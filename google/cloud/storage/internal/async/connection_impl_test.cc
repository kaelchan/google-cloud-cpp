// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "google/cloud/storage/internal/async/connection_impl.h"
#include "google/cloud/storage/async/writer_connection.h"
#include "google/cloud/storage/internal/async/default_options.h"
#include "google/cloud/storage/internal/async/write_payload_impl.h"
#include "google/cloud/storage/internal/crc32c.h"
#include "google/cloud/storage/internal/grpc/ctype_cord_workaround.h"
#include "google/cloud/storage/options.h"
#include "google/cloud/storage/retry_policy.h"
#include "google/cloud/storage/testing/canonical_errors.h"
#include "google/cloud/storage/testing/mock_hash_function.h"
#include "google/cloud/storage/testing/mock_resume_policy.h"
#include "google/cloud/storage/testing/mock_storage_stub.h"
#include "google/cloud/common_options.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/background_threads_impl.h"
#include "google/cloud/testing_util/async_sequencer.h"
#include "google/cloud/testing_util/chrono_output.h"
#include "google/cloud/testing_util/is_proto_equal.h"
#include "google/cloud/testing_util/mock_completion_queue_impl.h"
#include "google/cloud/testing_util/status_matchers.h"
#include "google/cloud/testing_util/validate_metadata.h"
#include <google/protobuf/text_format.h>
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace storage_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

using ::google::cloud::storage::testing::MockAsyncBidiWriteObjectStream;
using ::google::cloud::storage::testing::MockAsyncInsertStream;
using ::google::cloud::storage::testing::MockAsyncObjectMediaStream;
using ::google::cloud::storage::testing::MockHashFunction;
using ::google::cloud::storage::testing::MockResumePolicy;
using ::google::cloud::storage::testing::MockStorageStub;
using ::google::cloud::storage::testing::canonical_errors::PermanentError;
using ::google::cloud::storage::testing::canonical_errors::TransientError;
using ::google::cloud::testing_util::AsyncSequencer;
using ::google::cloud::testing_util::IsOk;
using ::google::cloud::testing_util::IsOkAndHolds;
using ::google::cloud::testing_util::IsProtoEqual;
using ::google::cloud::testing_util::MockCompletionQueueImpl;
using ::google::cloud::testing_util::StatusIs;
using ::google::cloud::testing_util::ValidateMetadataFixture;
using ::google::protobuf::TextFormat;
using ::testing::_;
using ::testing::AllOf;
using ::testing::ElementsAre;
using ::testing::HasSubstr;
using ::testing::Pair;
using ::testing::ResultOf;
using ::testing::Return;
using ::testing::UnorderedElementsAre;
using ::testing::VariantWith;

using AsyncWriteObjectStream =
    ::google::cloud::internal::AsyncStreamingWriteRpc<
        google::storage::v2::WriteObjectRequest,
        google::storage::v2::WriteObjectResponse>;

using AsyncReadObjectStream = ::google::cloud::internal::AsyncStreamingReadRpc<
    google::storage::v2::ReadObjectResponse>;

using AsyncBidiWriteObjectStream = ::google::cloud::AsyncStreamingReadWriteRpc<
    google::storage::v2::BidiWriteObjectRequest,
    google::storage::v2::BidiWriteObjectResponse>;

class AsyncConnectionImplTest : public ::testing::Test {
 protected:
  std::multimap<std::string, std::string> GetMetadata(
      grpc::ClientContext& context) {
    return validate_metadata_fixture_.GetMetadata(context);
  }

 private:
  ValidateMetadataFixture validate_metadata_fixture_;
};

auto constexpr kAuthority = "storage.googleapis.com";

auto TestOptions(Options options = {}) {
  using ms = std::chrono::milliseconds;
  options = internal::MergeOptions(
      std::move(options),
      Options{}
          .set<GrpcNumChannelsOption>(1)
          .set<storage::RetryPolicyOption>(
              storage::LimitedErrorCountRetryPolicy(2).clone())
          .set<storage::BackoffPolicyOption>(
              storage::ExponentialBackoffPolicy(ms(1), ms(2), 2.0).clone()));
  return DefaultOptionsAsync(std::move(options));
}

std::shared_ptr<storage_experimental::AsyncConnection> MakeTestConnection(
    CompletionQueue cq, std::shared_ptr<storage::testing::MockStorageStub> mock,
    Options options = {}) {
  return MakeAsyncConnection(std::move(cq), std::move(mock),
                             TestOptions(std::move(options)));
}

std::unique_ptr<AsyncWriteObjectStream> MakeErrorInsertStream(
    AsyncSequencer<bool>& sequencer, Status const& status) {
  auto stream = std::make_unique<MockAsyncInsertStream>();
  EXPECT_CALL(*stream, Start).WillOnce([&] {
    return sequencer.PushBack("Start");
  });
  EXPECT_CALL(*stream, Finish).WillOnce([&, status] {
    return sequencer.PushBack("Finish").then([status](auto) {
      return StatusOr<google::storage::v2::WriteObjectResponse>(status);
    });
  });
  return std::unique_ptr<AsyncWriteObjectStream>(std::move(stream));
}

std::unique_ptr<AsyncReadObjectStream> MakeErrorReadStream(
    AsyncSequencer<bool>& sequencer, Status const& status) {
  auto stream = std::make_unique<MockAsyncObjectMediaStream>();
  EXPECT_CALL(*stream, Start).WillOnce([&] {
    return sequencer.PushBack("Start");
  });
  EXPECT_CALL(*stream, Finish).WillOnce([&, status] {
    return sequencer.PushBack("Finish").then([status](auto) { return status; });
  });
  return std::unique_ptr<AsyncReadObjectStream>(std::move(stream));
}

std::unique_ptr<AsyncBidiWriteObjectStream> MakeErrorBidiWriteStream(
    AsyncSequencer<bool>& sequencer, Status const& status) {
  auto stream = std::make_unique<MockAsyncBidiWriteObjectStream>();
  EXPECT_CALL(*stream, Start).WillOnce([&] {
    return sequencer.PushBack("Start");
  });
  EXPECT_CALL(*stream, Finish).WillOnce([&, status] {
    return sequencer.PushBack("Finish").then([status](auto) { return status; });
  });
  return std::unique_ptr<AsyncBidiWriteObjectStream>(std::move(stream));
}

TEST_F(AsyncConnectionImplTest, AsyncInsertObject) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<MockStorageStub>();
  EXPECT_CALL(*mock, AsyncWriteObject)
      .WillOnce([&] {
        // Force at least one retry before verifying it works with successful
        // requests.
        return MakeErrorInsertStream(sequencer, TransientError());
      })
      .WillOnce([&](CompletionQueue const&,
                    // NOLINTNEXTLINE(performance-unnecessary-value-param)
                    std::shared_ptr<grpc::ClientContext> context,
                    // NOLINTNEXTLINE(performance-unnecessary-value-param)
                    internal::ImmutableOptions options) {
        EXPECT_EQ(options->get<AuthorityOption>(), kAuthority);
        auto metadata = GetMetadata(*context);
        EXPECT_THAT(metadata,
                    UnorderedElementsAre(
                        Pair("x-goog-quota-user", "test-quota-user"),
                        Pair("x-goog-fieldmask", "field1,field2"),
                        Pair("x-goog-request-params",
                             "bucket=projects%2F_%2Fbuckets%2Ftest-bucket"),
                        Pair("x-goog-gcs-idempotency-token", _)));
        auto stream = std::make_unique<MockAsyncInsertStream>();
        EXPECT_CALL(*stream, Start).WillOnce([&] {
          return sequencer.PushBack("Start");
        });
        EXPECT_CALL(*stream, Write).WillOnce([&](auto const& request, auto) {
          EXPECT_TRUE(request.has_write_object_spec());
          auto const& resource = request.write_object_spec().resource();
          EXPECT_THAT(resource.bucket(), "projects/_/buckets/test-bucket");
          EXPECT_THAT(resource.name(), "test-object");
          return sequencer.PushBack("Write");
        });
        EXPECT_CALL(*stream, Finish).WillOnce([&] {
          return sequencer.PushBack("Finish").then([](auto) {
            google::storage::v2::WriteObjectResponse response;
            response.mutable_resource()->set_bucket(
                "projects/_/buckets/test-bucket");
            response.mutable_resource()->set_name("test-object");
            response.mutable_resource()->set_size(123456);
            return make_status_or(response);
          });
        });
        EXPECT_CALL(*stream, GetRequestMetadata);
        return std::unique_ptr<AsyncWriteObjectStream>(std::move(stream));
      });

  auto mock_cq = std::make_shared<MockCompletionQueueImpl>();
  EXPECT_CALL(*mock_cq, MakeRelativeTimer).WillRepeatedly([&sequencer](auto d) {
    auto deadline =
        std::chrono::system_clock::now() +
        std::chrono::duration_cast<std::chrono::system_clock::duration>(d);
    return sequencer.PushBack("MakeRelativeTimer").then([deadline](auto f) {
      if (f.get()) return make_status_or(deadline);
      return StatusOr<std::chrono::system_clock::time_point>(
          Status(StatusCode::kCancelled, "cancelled"));
    });
  });

  auto connection =
      MakeTestConnection(CompletionQueue(mock_cq), mock,
                         // Disable transfer timeouts in this test.
                         Options{}.set<storage::TransferStallTimeoutOption>(
                             std::chrono::seconds(0)));
  auto pending = connection->InsertObject(
      {storage_experimental::InsertObjectRequest("test-bucket", "test-object")
           .set_multiple_options(storage::Fields("field1,field2"),
                                 storage::QuotaUser("test-quota-user")),
       storage_experimental::WritePayload(),
       /*.options=*/connection->options()});

  // Simulate a transient failure.
  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(false);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(false);

  // The retry loop should create a timer.
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "MakeRelativeTimer");
  next.first.set_value(true);

  // Simulate a successful request.
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Write");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);

  auto response = pending.get();
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(response->bucket(), "test-bucket");
  EXPECT_EQ(response->name(), "test-object");
  EXPECT_EQ(response->size(), 123456);
  EXPECT_THAT(response->self_link(), HasSubstr("test-object"));
}

TEST_F(AsyncConnectionImplTest, AsyncInsertObjectWithTimeout) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<MockStorageStub>();
  EXPECT_CALL(*mock, AsyncWriteObject).WillOnce([&] {
    auto stream = std::make_unique<MockAsyncInsertStream>();
    EXPECT_CALL(*stream, Start).WillOnce([&] {
      return sequencer.PushBack("Start");
    });
    EXPECT_CALL(*stream, Write).WillOnce([&](auto const& request, auto) {
      EXPECT_TRUE(request.has_write_object_spec());
      auto const& resource = request.write_object_spec().resource();
      EXPECT_THAT(resource.bucket(), "projects/_/buckets/test-bucket");
      EXPECT_THAT(resource.name(), "test-object");
      return sequencer.PushBack("Write");
    });
    EXPECT_CALL(*stream, Finish).WillOnce([&] {
      return sequencer.PushBack("Finish").then([](auto) {
        google::storage::v2::WriteObjectResponse response;
        response.mutable_resource()->set_bucket(
            "projects/_/buckets/test-bucket");
        response.mutable_resource()->set_name("test-object");
        response.mutable_resource()->set_size(123456);
        return make_status_or(response);
      });
    });
    EXPECT_CALL(*stream, GetRequestMetadata);
    return std::unique_ptr<AsyncWriteObjectStream>(std::move(stream));
  });

  auto mock_cq = std::make_shared<MockCompletionQueueImpl>();
  // We will configure the connection to use 1 second timeouts.
  EXPECT_CALL(*mock_cq, MakeRelativeTimer(
                            std::chrono::nanoseconds(std::chrono::seconds(1))))
      .WillRepeatedly([&sequencer](auto d) {
        auto deadline =
            std::chrono::system_clock::now() +
            std::chrono::duration_cast<std::chrono::system_clock::duration>(d);
        return sequencer.PushBack("MakeRelativeTimer").then([deadline](auto f) {
          if (f.get()) return make_status_or(deadline);
          return StatusOr<std::chrono::system_clock::time_point>(
              Status(StatusCode::kCancelled, "cancelled"));
        });
      });

  auto connection = MakeTestConnection(
      CompletionQueue(mock_cq), mock,
      // Disable transfer timeouts in this test.
      Options{}
          .set<storage::TransferStallTimeoutOption>(std::chrono::seconds(1))
          .set<storage::TransferStallMinimumRateOption>(2 * 1024 * 1024L));
  auto pending = connection->InsertObject(
      {storage_experimental::InsertObjectRequest("test-bucket", "test-object")
           .set_multiple_options(storage::Fields("field1,field2"),
                                 storage::QuotaUser("test-quota-user")),
       storage_experimental::WritePayload(),
       /*.options=*/connection->options()});

  // Because the timeout parameters are configured, the first thing to happen is
  // that a timer is set.
  auto timer = sequencer.PopFrontWithName();
  EXPECT_EQ(timer.second, "MakeRelativeTimer");
  // Then the `Start()` operation is scheduled.  Either that complete first (and
  // then cancels the timer) or the timer completes first (and cancels the
  // streaming RPC).
  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  timer.first.set_value(false);  // simulate a cancelled timer.
  next.first.set_value(true);

  timer = sequencer.PopFrontWithName();
  EXPECT_EQ(timer.second, "MakeRelativeTimer");
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Write");
  timer.first.set_value(false);  // simulate a cancelled timer.
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);

  auto response = pending.get();
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(response->bucket(), "test-bucket");
  EXPECT_EQ(response->name(), "test-object");
  EXPECT_EQ(response->size(), 123456);
  EXPECT_THAT(response->self_link(), HasSubstr("test-object"));
}

TEST_F(AsyncConnectionImplTest, AsyncInsertObjectPermanentError) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<MockStorageStub>();
  EXPECT_CALL(*mock, AsyncWriteObject).WillOnce([&] {
    return MakeErrorInsertStream(sequencer, PermanentError());
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->InsertObject(
      {storage_experimental::InsertObjectRequest("test-bucket", "test-object")
           .set_multiple_options(storage::Fields("field1,field2"),
                                 storage::QuotaUser("test-quota-user")),
       storage_experimental::WritePayload(),
       /*.options=*/connection->options()});

  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(false);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(false);

  auto response = pending.get();
  ASSERT_THAT(response, StatusIs(PermanentError().code()));
}

TEST_F(AsyncConnectionImplTest, AsyncInsertObjectTooManyTransients) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<MockStorageStub>();
  EXPECT_CALL(*mock, AsyncWriteObject).Times(3).WillRepeatedly([&] {
    return MakeErrorInsertStream(sequencer, TransientError());
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->InsertObject(
      {storage_experimental::InsertObjectRequest("test-bucket", "test-object")
           .set_multiple_options(storage::Fields("field1,field2"),
                                 storage::QuotaUser("test-quota-user")),
       storage_experimental::WritePayload(),
       /*.options=*/connection->options()});

  for (int i = 0; i != 3; ++i) {
    auto next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "Start");
    next.first.set_value(false);

    next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "Finish");
    next.first.set_value(false);
  }

  auto response = pending.get();
  ASSERT_THAT(response, StatusIs(TransientError().code()));
}

TEST_F(AsyncConnectionImplTest, AsyncReadObject) {
  AsyncSequencer<bool> sequencer;
  auto make_success_stream = [&](AsyncSequencer<bool>& sequencer) {
    auto stream = std::make_unique<MockAsyncObjectMediaStream>();
    EXPECT_CALL(*stream, Start).WillOnce([&] {
      return sequencer.PushBack("Start");
    });
    EXPECT_CALL(*stream, Read)
        .WillOnce([&] {
          return sequencer.PushBack("Read").then([](auto) {
            google::storage::v2::ReadObjectResponse response;
            response.mutable_metadata()->set_bucket(
                "projects/_/buckets/test-bucket");
            response.mutable_metadata()->set_name("test-object");
            response.mutable_metadata()->set_size(4096);
            response.mutable_content_range()->set_start(1024);
            response.mutable_content_range()->set_end(2048);
            return absl::make_optional(response);
          });
        })
        .WillOnce([&] {
          return sequencer.PushBack("Read").then([](auto) {
            return absl::optional<google::storage::v2::ReadObjectResponse>();
          });
        });
    EXPECT_CALL(*stream, Finish).WillOnce([&] {
      return sequencer.PushBack("Finish").then([](auto) { return Status{}; });
    });
    return std::unique_ptr<AsyncReadObjectStream>(std::move(stream));
  };

  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncReadObject)
      .WillOnce(
          [&] { return MakeErrorReadStream(sequencer, TransientError()); })
      .WillOnce([&](CompletionQueue const&,
                    // NOLINTNEXTLINE(performance-unnecessary-value-param)
                    std::shared_ptr<grpc::ClientContext> context,
                    // NOLINTNEXTLINE(performance-unnecessary-value-param)
                    google::cloud::internal::ImmutableOptions options,
                    google::storage::v2::ReadObjectRequest const& request) {
        // Verify at least one option is initialized with the correct
        // values.
        EXPECT_EQ(options->get<AuthorityOption>(), kAuthority);
        auto metadata = GetMetadata(*context);
        EXPECT_THAT(metadata, UnorderedElementsAre(
                                  Pair("x-goog-quota-user", "test-quota-user"),
                                  Pair("x-goog-fieldmask", "field1,field2")));
        EXPECT_THAT(request.bucket(), "projects/_/buckets/test-bucket");
        EXPECT_THAT(request.object(), "test-object");
        return make_success_stream(sequencer);
      });

  auto mock_cq = std::make_shared<MockCompletionQueueImpl>();
  EXPECT_CALL(*mock_cq, MakeRelativeTimer).WillRepeatedly([&sequencer](auto d) {
    auto deadline =
        std::chrono::system_clock::now() +
        std::chrono::duration_cast<std::chrono::system_clock::duration>(d);
    return sequencer.PushBack("MakeRelativeTimer").then([deadline](auto f) {
      if (f.get()) return make_status_or(deadline);
      return StatusOr<std::chrono::system_clock::time_point>(
          Status(StatusCode::kCancelled, "cancelled"));
    });
  });

  auto connection =
      MakeTestConnection(CompletionQueue(mock_cq), mock,
                         Options{}.set<storage::DownloadStallTimeoutOption>(
                             std::chrono::seconds(0)));
  auto pending = connection->ReadObject(
      {storage_experimental::ReadObjectRequest("test-bucket", "test-object")
           .set_multiple_options(storage::Fields("field1,field2"),
                                 storage::QuotaUser("test-quota-user")),
       connection->options()});

  ASSERT_TRUE(pending.is_ready());
  auto r = pending.get();
  ASSERT_STATUS_OK(r);
  auto reader = *std::move(r);
  auto data = reader->Read();

  // First simulate a failed `ReadObject()`. This returns a streaming RPC
  // that completes with `false` on `Start()` (i.e. never starts) and then
  // completes with a transient error on `Finish()`.
  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(false);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);

  // The retry loop will set a timer to backoff.
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "MakeRelativeTimer");
  next.first.set_value(true);

  // Then simulate a successful `ReadObject()`. This returns a streaming
  // RPC that completes with `true` on `Start()`, then returns some data on the
  // first `Read()`, then an unset optional on the second `Read()` (indicating
  // 'end of the streaming RPC'), and then a success `Status` for `Finish()`.
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  next.first.set_value(true);
  auto response = data.get();
  ASSERT_TRUE(
      absl::holds_alternative<storage_experimental::ReadPayload>(response));

  // The `Read()` and `Finish()` calls must happen before the second `Read()` is
  // satisfied.
  data = reader->Read();
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);

  EXPECT_THAT(data.get(), VariantWith<Status>(IsOk()));
}

TEST_F(AsyncConnectionImplTest, AsyncReadObjectWithTimeout) {
  AsyncSequencer<bool> sequencer;

  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncReadObject).WillOnce([&] {
    auto stream = std::make_unique<MockAsyncObjectMediaStream>();
    EXPECT_CALL(*stream, Start).WillOnce([&] {
      return sequencer.PushBack("Start");
    });
    EXPECT_CALL(*stream, Read)
        .WillOnce([&] {
          return sequencer.PushBack("Read").then([](auto) {
            google::storage::v2::ReadObjectResponse response;
            response.mutable_metadata()->set_bucket(
                "projects/_/buckets/test-bucket");
            response.mutable_metadata()->set_name("test-object");
            response.mutable_metadata()->set_size(4096);
            response.mutable_content_range()->set_start(1024);
            response.mutable_content_range()->set_end(2048);
            return absl::make_optional(response);
          });
        })
        .WillOnce([&] {
          return sequencer.PushBack("Read").then([](auto) {
            return absl::optional<google::storage::v2::ReadObjectResponse>();
          });
        });
    EXPECT_CALL(*stream, Finish).WillOnce([&] {
      return sequencer.PushBack("Finish").then([](auto) { return Status{}; });
    });
    return std::unique_ptr<AsyncReadObjectStream>(std::move(stream));
  });

  auto mock_cq = std::make_shared<MockCompletionQueueImpl>();
  // We will configure the connection to use 1 second timeouts.
  EXPECT_CALL(*mock_cq, MakeRelativeTimer(
                            std::chrono::nanoseconds(std::chrono::seconds(1))))
      .WillRepeatedly([&sequencer](auto d) {
        auto deadline =
            std::chrono::system_clock::now() +
            std::chrono::duration_cast<std::chrono::system_clock::duration>(d);
        return sequencer.PushBack("MakeRelativeTimer").then([deadline](auto f) {
          if (f.get()) return make_status_or(deadline);
          return StatusOr<std::chrono::system_clock::time_point>(
              Status(StatusCode::kCancelled, "cancelled"));
        });
      });

  auto connection = MakeTestConnection(
      CompletionQueue(mock_cq), mock,
      Options{}
          .set<storage::DownloadStallTimeoutOption>(std::chrono::seconds(1))
          .set<storage::DownloadStallMinimumRateOption>(2 * 1024 * 1024L));
  auto pending = connection->ReadObject(
      {storage_experimental::ReadObjectRequest("test-bucket", "test-object")
           .set_multiple_options(storage::Fields("field1,field2"),
                                 storage::QuotaUser("test-quota-user")),
       connection->options()});

  ASSERT_TRUE(pending.is_ready());
  auto r = pending.get();
  ASSERT_STATUS_OK(r);
  auto reader = *std::move(r);

  // Start a read.
  auto data = reader->Read();
  // Because the timeout parameters are configured, the first thing to happen is
  // that a timer is set.
  auto timer = sequencer.PopFrontWithName();
  EXPECT_EQ(timer.second, "MakeRelativeTimer");
  // Then the `Start()` operation is scheduled.  Either that complete first (and
  // then cancels the timer) or the timer completes first (and cancels the
  // streaming RPC).
  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  timer.first.set_value(false);  // simulate a cancelled timer.
  next.first.set_value(true);

  // Then the `Read()` operation and its timer are scheduled:
  timer = sequencer.PopFrontWithName();
  EXPECT_EQ(timer.second, "MakeRelativeTimer");
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  timer.first.set_value(false);  // simulate a cancelled timer.
  next.first.set_value(true);

  auto response = data.get();
  ASSERT_TRUE(
      absl::holds_alternative<storage_experimental::ReadPayload>(response));

  // Trigger another read. Since this closes the stream, the `Read()` and
  // `Finish()` calls must happen before the second `Read()` is satisfied.
  data = reader->Read();
  timer = sequencer.PopFrontWithName();
  EXPECT_EQ(timer.second, "MakeRelativeTimer");
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  timer.first.set_value(false);  // simulate a canceled timeout
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);

  EXPECT_THAT(data.get(), VariantWith<Status>(IsOk()));
}

TEST_F(AsyncConnectionImplTest, AsyncReadObjectDetectBadMessageChecksum) {
  AsyncSequencer<bool> sequencer;
  auto make_bad_checksum_stream = [&](AsyncSequencer<bool>& sequencer) {
    auto stream = std::make_unique<MockAsyncObjectMediaStream>();
    EXPECT_CALL(*stream, Start).WillOnce([&] {
      return sequencer.PushBack("Start");
    });
    EXPECT_CALL(*stream, Read).WillOnce([&] {
      return sequencer.PushBack("Read").then([](auto) {
        google::storage::v2::ReadObjectResponse response;
        response.mutable_metadata()->set_bucket(
            "projects/_/buckets/test-bucket");
        response.mutable_metadata()->set_name("test-object");
        response.mutable_metadata()->set_generation(12345);
        auto constexpr kQuick = "The quick brown fox jumps over the lazy dog";
        SetMutableContent(*response.mutable_checksummed_data(),
                          ContentType(kQuick));
        // Deliberatively set the checksum to an incorrect value.
        response.mutable_checksummed_data()->set_crc32c(Crc32c(kQuick) + 1);
        return absl::make_optional(response);
      });
    });
    EXPECT_CALL(*stream, Finish).WillOnce([&] {
      return sequencer.PushBack("Finish").then([](auto) { return Status{}; });
    });
    return std::unique_ptr<AsyncReadObjectStream>(std::move(stream));
  };

  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncReadObject).WillOnce([&] {
    return make_bad_checksum_stream(sequencer);
  });

  auto mock_resume_policy_factory =
      []() -> std::unique_ptr<storage_experimental::ResumePolicy> {
    auto policy = std::make_unique<MockResumePolicy>();
    EXPECT_CALL(*policy, OnStartSuccess).Times(1);
    EXPECT_CALL(*policy, OnFinish(StatusIs(StatusCode::kInvalidArgument)))
        .WillOnce(Return(storage_experimental::ResumePolicy::kStop));
    return policy;
  };

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(
      pool.cq(), mock,
      Options{}.set<storage_experimental::ResumePolicyOption>(
          mock_resume_policy_factory));
  auto pending = connection->ReadObject(
      {storage_experimental::ReadObjectRequest("test-bucket", "test-object")
           .set_multiple_options(storage::Fields("field1,field2"),
                                 storage::QuotaUser("test-quota-user")),
       connection->options()});

  ASSERT_TRUE(pending.is_ready());
  auto r = pending.get();
  ASSERT_STATUS_OK(r);
  auto reader = *std::move(r);
  auto data = reader->Read();

  // This stream starts successfully:
  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(true);

  // However, the `Read()` call returns an error because the checksum is invalid
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  next.first.set_value(true);
  auto response = data.get();
  EXPECT_THAT(response,
              VariantWith<Status>(StatusIs(StatusCode::kInvalidArgument)));

  // The stream Finish() function should be called in the background.
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);
}

TEST_F(AsyncConnectionImplTest, AsyncReadObjectDetectBadFullChecksum) {
  auto constexpr kQuick = "The quick brown fox jumps over the lazy dog";
  AsyncSequencer<bool> sequencer;
  auto make_bad_checksum_stream = [&](AsyncSequencer<bool>& sequencer) {
    auto stream = std::make_unique<MockAsyncObjectMediaStream>();
    EXPECT_CALL(*stream, Start).WillOnce([&] {
      return sequencer.PushBack("Start");
    });
    EXPECT_CALL(*stream, Read)
        .WillOnce([&] {
          return sequencer.PushBack("Read").then([&](auto) {
            google::storage::v2::ReadObjectResponse response;
            response.mutable_metadata()->set_bucket(
                "projects/_/buckets/test-bucket");
            response.mutable_metadata()->set_name("test-object");
            response.mutable_metadata()->set_generation(12345);
            SetMutableContent(*response.mutable_checksummed_data(),
                              ContentType(kQuick));
            response.mutable_checksummed_data()->set_crc32c(Crc32c(kQuick));
            // Set the full object checksums to an intentionally incorrect
            // value. The client should detect this error and report it at the
            // end of the download.
            auto full_crc32c = std::uint32_t{0};
            full_crc32c = ExtendCrc32c(full_crc32c, kQuick);
            full_crc32c = ExtendCrc32c(full_crc32c, kQuick);
            response.mutable_object_checksums()->set_crc32c(full_crc32c + 1);
            return absl::make_optional(response);
          });
        })
        .WillOnce([&] {
          return sequencer.PushBack("Read").then([&](auto) {
            google::storage::v2::ReadObjectResponse response;
            SetMutableContent(*response.mutable_checksummed_data(),
                              ContentType(kQuick));
            response.mutable_checksummed_data()->set_crc32c(Crc32c(kQuick));
            return absl::make_optional(response);
          });
        })
        .WillOnce([&] {
          return sequencer.PushBack("Read").then([](auto) {
            return absl::optional<google::storage::v2::ReadObjectResponse>{};
          });
        });
    EXPECT_CALL(*stream, Finish).WillOnce([&] {
      return sequencer.PushBack("Finish").then([](auto) { return Status{}; });
    });
    return std::unique_ptr<AsyncReadObjectStream>(std::move(stream));
  };

  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncReadObject).WillOnce([&] {
    return make_bad_checksum_stream(sequencer);
  });

  auto mock_resume_policy_factory =
      []() -> std::unique_ptr<storage_experimental::ResumePolicy> {
    auto policy = std::make_unique<MockResumePolicy>();
    EXPECT_CALL(*policy, OnStartSuccess).Times(1);
    EXPECT_CALL(*policy, OnFinish).Times(0);
    return policy;
  };

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(
      pool.cq(), mock,
      Options{}.set<storage_experimental::ResumePolicyOption>(
          mock_resume_policy_factory));
  auto pending = connection->ReadObject(
      {storage_experimental::ReadObjectRequest("test-bucket", "test-object")
           .set_multiple_options(storage::Fields("field1,field2"),
                                 storage::QuotaUser("test-quota-user")),
       connection->options()});

  ASSERT_TRUE(pending.is_ready());
  auto r = pending.get();
  ASSERT_STATUS_OK(r);
  auto reader = *std::move(r);
  auto data = reader->Read();

  // This stream starts successfully:
  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(true);

  // We expect two `Read()` calls with the same contents and with valid CRC32C
  // values.
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  next.first.set_value(true);
  auto response = data.get();
  EXPECT_THAT(response, VariantWith<storage_experimental::ReadPayload>(ResultOf(
                            "payload contents",
                            [](storage_experimental::ReadPayload const& p) {
                              return p.contents();
                            },
                            ElementsAre(std::string(kQuick)))));

  // Trigger the second `Read()` and simulate its behavior.
  data = reader->Read();
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  next.first.set_value(true);
  response = data.get();
  EXPECT_THAT(response, VariantWith<storage_experimental::ReadPayload>(ResultOf(
                            "payload contents",
                            [](storage_experimental::ReadPayload const& p) {
                              return p.contents();
                            },
                            ElementsAre(std::string(kQuick)))));

  // The last Read() triggers the end of stream message, including a call to
  // `Finish()`. It should detect the invalid checksum.
  data = reader->Read();
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  next.first.set_value(true);
  // The stream Finish() function should be called in the background.
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);

  response = data.get();
  EXPECT_THAT(response,
              VariantWith<Status>(StatusIs(StatusCode::kInvalidArgument)));
}

TEST_F(AsyncConnectionImplTest, AsyncReadObjectMalformedRequestError) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncReadObject).Times(0);

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->ReadObject(
      {storage_experimental::ReadObjectRequest("test-bucket", "test-object")
           .set_multiple_options(storage::EncryptionKey(
               storage::EncryptionKeyData{"invalid", "invalid", "invalid"})),
       connection->options()});
  ASSERT_TRUE(pending.is_ready());
  auto r = pending.get();
  EXPECT_THAT(r, StatusIs(StatusCode::kInvalidArgument));
}

TEST_F(AsyncConnectionImplTest, AsyncReadObjectPermanentError) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncReadObject).WillOnce([&] {
    return MakeErrorReadStream(sequencer, PermanentError());
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->ReadObject(
      {storage_experimental::ReadObjectRequest("test-bucket", "test-object"),
       connection->options()});
  ASSERT_TRUE(pending.is_ready());
  auto r = pending.get();
  ASSERT_STATUS_OK(r);
  auto reader = *std::move(r);
  auto data = reader->Read();

  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(false);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);

  auto response = data.get();
  EXPECT_THAT(response, VariantWith<Status>(StatusIs(PermanentError().code())));
}

TEST_F(AsyncConnectionImplTest, AsyncReadObjectTooManyTransients) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncReadObject).Times(3).WillRepeatedly([&] {
    return MakeErrorReadStream(sequencer, TransientError());
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->ReadObject(
      {storage_experimental::ReadObjectRequest("test-bucket", "test-object"),
       connection->options()});
  auto r = pending.get();
  ASSERT_STATUS_OK(r);
  auto reader = *std::move(r);
  auto data = reader->Read();

  for (int i = 0; i != 3; ++i) {
    auto next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "Start");
    next.first.set_value(false);

    next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "Finish");
    next.first.set_value(true);
  }

  auto response = data.get();
  EXPECT_THAT(response, VariantWith<Status>(StatusIs(TransientError().code())));
}

TEST_F(AsyncConnectionImplTest, UnbufferedUploadNewUpload) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncStartResumableWrite)
      .WillOnce([&] {
        return sequencer.PushBack("StartResumableWrite(1)").then([](auto) {
          return StatusOr<google::storage::v2::StartResumableWriteResponse>(
              TransientError());
        });
      })
      .WillOnce(
          [&](auto&, auto, auto,
              google::storage::v2::StartResumableWriteRequest const& request) {
            auto const& spec = request.write_object_spec();
            EXPECT_TRUE(spec.has_if_generation_match());
            EXPECT_EQ(spec.if_generation_match(), 123);
            auto const& resource = spec.resource();
            EXPECT_EQ(resource.bucket(), "projects/_/buckets/test-bucket");
            EXPECT_EQ(resource.name(), "test-object");
            EXPECT_EQ(resource.content_type(), "text/plain");

            return sequencer.PushBack("StartResumableWrite(2)").then([](auto) {
              auto response =
                  google::storage::v2::StartResumableWriteResponse{};
              response.set_upload_id("test-upload-id");
              return make_status_or(response);
            });
          });
  EXPECT_CALL(*mock, AsyncBidiWriteObject)
      .WillOnce(
          [&] { return MakeErrorBidiWriteStream(sequencer, TransientError()); })
      .WillOnce([&]() {
        auto stream = std::make_unique<MockAsyncBidiWriteObjectStream>();
        EXPECT_CALL(*stream, Start).WillOnce([&] {
          return sequencer.PushBack("Start");
        });
        EXPECT_CALL(*stream, Write)
            .WillOnce(
                [&](google::storage::v2::BidiWriteObjectRequest const& request,
                    grpc::WriteOptions wopt) {
                  EXPECT_TRUE(request.has_upload_id());
                  EXPECT_EQ(request.upload_id(), "test-upload-id");
                  EXPECT_FALSE(wopt.is_last_message());
                  return sequencer.PushBack("Write");
                })
            .WillOnce(
                [&](google::storage::v2::BidiWriteObjectRequest const& request,
                    grpc::WriteOptions wopt) {
                  EXPECT_FALSE(request.has_upload_id());
                  EXPECT_TRUE(request.finish_write());
                  EXPECT_TRUE(request.has_object_checksums());
                  EXPECT_TRUE(wopt.is_last_message());
                  return sequencer.PushBack("Write");
                });
        EXPECT_CALL(*stream, Read).WillOnce([&] {
          return sequencer.PushBack("Read").then([](auto) {
            auto response = google::storage::v2::BidiWriteObjectResponse{};
            response.mutable_resource()->set_bucket(
                "projects/_/buckets/test-bucket");
            response.mutable_resource()->set_name("test-object");
            response.mutable_resource()->set_generation(123456);
            return absl::make_optional(std::move(response));
          });
        });
        EXPECT_CALL(*stream, Cancel).Times(1);
        EXPECT_CALL(*stream, Finish).WillOnce([&] {
          return sequencer.PushBack("Finish").then(
              [](auto) { return Status{}; });
        });
        return std::unique_ptr<AsyncBidiWriteObjectStream>(std::move(stream));
      });

  auto mock_cq = std::make_shared<MockCompletionQueueImpl>();
  // We will configure the connection to use disable timeouts, this is just used
  // for the retry loop backoff timers.
  EXPECT_CALL(*mock_cq, MakeRelativeTimer).WillRepeatedly([&sequencer](auto d) {
    auto deadline =
        std::chrono::system_clock::now() +
        std::chrono::duration_cast<std::chrono::system_clock::duration>(d);
    return sequencer.PushBack("MakeRelativeTimer").then([deadline](auto f) {
      if (f.get()) return make_status_or(deadline);
      return StatusOr<std::chrono::system_clock::time_point>(
          Status(StatusCode::kCancelled, "cancelled"));
    });
  });
  auto connection =
      MakeTestConnection(CompletionQueue(mock_cq), mock,
                         Options{}.set<storage::TransferStallTimeoutOption>(
                             std::chrono::seconds(0)));
  auto pending = connection->StartUnbufferedUpload(
      {storage_experimental::ResumableUploadRequest("test-bucket",
                                                    "test-object")
           .set_multiple_options(
               storage::WithObjectMetadata(
                   storage::ObjectMetadata{}.set_content_type("text/plain")),
               storage::IfGenerationMatch(123)),
       connection->options()});

  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "StartResumableWrite(1)");
  next.first.set_value(true);

  // The retry loop should start a backoff timer.
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "MakeRelativeTimer");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "StartResumableWrite(2)");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(false);  // The first stream fails

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(false);

  // The retry loop should start a backoff timer.
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "MakeRelativeTimer");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(true);

  auto r = pending.get();
  ASSERT_STATUS_OK(r);
  auto writer = *std::move(r);
  EXPECT_EQ(writer->UploadId(), "test-upload-id");
  EXPECT_EQ(absl::get<std::int64_t>(writer->PersistedState()), 0);

  auto w1 = writer->Write({});
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Write");
  next.first.set_value(true);
  EXPECT_STATUS_OK(w1.get());

  auto w2 = writer->Finalize({});
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Write");
  next.first.set_value(true);
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  next.first.set_value(true);

  auto response = w2.get();
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(response->bucket(), "test-bucket");
  EXPECT_EQ(response->name(), "test-object");
  EXPECT_EQ(response->generation(), 123456);

  writer.reset();
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);
}

TEST_F(AsyncConnectionImplTest, UnbufferedUploadNewUploadWithTimeout) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncStartResumableWrite).WillOnce([&sequencer] {
    return sequencer.PushBack("StartResumableWrite").then([](auto) {
      auto response = google::storage::v2::StartResumableWriteResponse{};
      response.set_upload_id("test-upload-id");
      return make_status_or(response);
    });
  });
  EXPECT_CALL(*mock, AsyncBidiWriteObject).WillOnce([&]() {
    auto stream = std::make_unique<MockAsyncBidiWriteObjectStream>();
    EXPECT_CALL(*stream, Start).WillOnce([&sequencer] {
      return sequencer.PushBack("Start");
    });
    EXPECT_CALL(*stream, Write).WillOnce([&sequencer] {
      return sequencer.PushBack("Write");
    });
    EXPECT_CALL(*stream, Read).WillOnce([&sequencer] {
      return sequencer.PushBack("Read").then([](auto) {
        auto response = google::storage::v2::BidiWriteObjectResponse{};
        response.mutable_resource()->set_bucket(
            "projects/_/buckets/test-bucket");
        response.mutable_resource()->set_name("test-object");
        response.mutable_resource()->set_generation(123456);
        return absl::make_optional(std::move(response));
      });
    });
    EXPECT_CALL(*stream, Cancel).Times(1);
    EXPECT_CALL(*stream, Finish).WillOnce([&sequencer] {
      return sequencer.PushBack("Finish").then([](auto) { return Status{}; });
    });
    return std::unique_ptr<AsyncBidiWriteObjectStream>(std::move(stream));
  });

  auto mock_cq = std::make_shared<MockCompletionQueueImpl>();
  // We will configure the connection to use 1 second timeouts.
  EXPECT_CALL(*mock_cq, MakeRelativeTimer(
                            std::chrono::nanoseconds(std::chrono::seconds(1))))
      .WillRepeatedly([&sequencer](auto d) {
        auto deadline =
            std::chrono::system_clock::now() +
            std::chrono::duration_cast<std::chrono::system_clock::duration>(d);
        return sequencer.PushBack("MakeRelativeTimer").then([deadline](auto f) {
          if (f.get()) return make_status_or(deadline);
          return StatusOr<std::chrono::system_clock::time_point>(
              Status(StatusCode::kCancelled, "cancelled"));
        });
      });
  auto connection = MakeTestConnection(
      CompletionQueue(mock_cq), mock,
      Options{}
          .set<storage::TransferStallTimeoutOption>(std::chrono::seconds(1))
          .set<storage::TransferStallMinimumRateOption>(2 * 1024 * 1024L));
  auto pending = connection->StartUnbufferedUpload(
      {storage_experimental::ResumableUploadRequest("test-bucket",
                                                    "test-object")
           .set_multiple_options(
               storage::WithObjectMetadata(
                   storage::ObjectMetadata{}.set_content_type("text/plain")),
               storage::IfGenerationMatch(123)),
       connection->options()});

  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "StartResumableWrite");
  next.first.set_value(true);

  auto timer = sequencer.PopFrontWithName();
  EXPECT_EQ(timer.second, "MakeRelativeTimer");
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  timer.first.set_value(false);  // simulate a cancelled timer.
  next.first.set_value(true);

  auto r = pending.get();
  ASSERT_STATUS_OK(r);
  auto writer = *std::move(r);
  EXPECT_EQ(writer->UploadId(), "test-upload-id");
  EXPECT_EQ(absl::get<std::int64_t>(writer->PersistedState()), 0);

  auto w2 = writer->Finalize({});
  timer = sequencer.PopFrontWithName();
  EXPECT_EQ(timer.second, "MakeRelativeTimer");
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Write");
  timer.first.set_value(false);  // simulate a cancelled timer.
  next.first.set_value(true);
  timer = sequencer.PopFrontWithName();
  EXPECT_EQ(timer.second, "MakeRelativeTimer");
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  timer.first.set_value(false);  // simulate a cancelled timer.
  next.first.set_value(true);

  auto response = w2.get();
  ASSERT_STATUS_OK(response);

  writer.reset();
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);
}

TEST_F(AsyncConnectionImplTest, UnbufferedUploadResumeUpload) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncQueryWriteStatus)
      .WillOnce([&] {
        return sequencer.PushBack("QueryWriteStatus(1)").then([](auto) {
          return StatusOr<google::storage::v2::QueryWriteStatusResponse>(
              TransientError());
        });
      })
      .WillOnce(
          [&](auto&, auto, auto,
              google::storage::v2::QueryWriteStatusRequest const& request) {
            EXPECT_EQ(request.upload_id(), "test-upload-id");

            return sequencer.PushBack("QueryWriteStatus(2)").then([](auto) {
              auto response = google::storage::v2::QueryWriteStatusResponse{};
              response.set_persisted_size(16384);
              return make_status_or(response);
            });
          });
  EXPECT_CALL(*mock, AsyncBidiWriteObject)
      .WillOnce(
          [&] { return MakeErrorBidiWriteStream(sequencer, TransientError()); })
      .WillOnce([&]() {
        auto stream = std::make_unique<MockAsyncBidiWriteObjectStream>();
        EXPECT_CALL(*stream, Start).WillOnce([&] {
          return sequencer.PushBack("Start");
        });
        EXPECT_CALL(*stream, Write)
            .WillOnce(
                [&](google::storage::v2::BidiWriteObjectRequest const& request,
                    grpc::WriteOptions wopt) {
                  EXPECT_TRUE(request.has_upload_id());
                  EXPECT_EQ(request.upload_id(), "test-upload-id");
                  EXPECT_FALSE(wopt.is_last_message());
                  return sequencer.PushBack("Write");
                })
            .WillOnce(
                [&](google::storage::v2::BidiWriteObjectRequest const& request,
                    grpc::WriteOptions wopt) {
                  EXPECT_FALSE(request.has_upload_id());
                  EXPECT_TRUE(request.finish_write());
                  EXPECT_TRUE(request.has_object_checksums());
                  EXPECT_TRUE(wopt.is_last_message());
                  return sequencer.PushBack("Write");
                });
        EXPECT_CALL(*stream, Read).WillOnce([&] {
          return sequencer.PushBack("Read").then([](auto) {
            auto response = google::storage::v2::BidiWriteObjectResponse{};
            response.mutable_resource()->set_bucket(
                "projects/_/buckets/test-bucket");
            response.mutable_resource()->set_name("test-object");
            response.mutable_resource()->set_generation(123456);
            return absl::make_optional(std::move(response));
          });
        });
        EXPECT_CALL(*stream, Cancel).Times(1);
        EXPECT_CALL(*stream, Finish).WillOnce([&] {
          return sequencer.PushBack("Finish").then(
              [](auto) { return Status{}; });
        });
        return std::unique_ptr<AsyncBidiWriteObjectStream>(std::move(stream));
      });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->StartUnbufferedUpload(
      {storage_experimental::ResumableUploadRequest("test-bucket",
                                                    "test-object")
           .set_multiple_options(
               storage::UseResumableUploadSession("test-upload-id")),
       connection->options()});

  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "QueryWriteStatus(1)");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "QueryWriteStatus(2)");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(false);  // The first stream fails

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(false);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(true);

  auto r = pending.get();
  ASSERT_STATUS_OK(r);
  auto writer = *std::move(r);
  EXPECT_EQ(writer->UploadId(), "test-upload-id");
  EXPECT_EQ(absl::get<std::int64_t>(writer->PersistedState()), 16384);

  auto w1 = writer->Write({});
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Write");
  next.first.set_value(true);
  EXPECT_STATUS_OK(w1.get());

  auto w2 = writer->Finalize({});
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Write");
  next.first.set_value(true);
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  next.first.set_value(true);

  auto response = w2.get();
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(response->bucket(), "test-bucket");
  EXPECT_EQ(response->name(), "test-object");
  EXPECT_EQ(response->generation(), 123456);

  writer.reset();
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);
}

TEST_F(AsyncConnectionImplTest, UnbufferedUploadResumeFinalizedUpload) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncQueryWriteStatus)
      .WillOnce([&] {
        return sequencer.PushBack("QueryWriteStatus(1)").then([](auto) {
          return StatusOr<google::storage::v2::QueryWriteStatusResponse>(
              TransientError());
        });
      })
      .WillOnce(
          [&](auto&, auto, auto,
              google::storage::v2::QueryWriteStatusRequest const& request) {
            EXPECT_EQ(request.upload_id(), "test-upload-id");

            return sequencer.PushBack("QueryWriteStatus(2)").then([](auto) {
              auto response = google::storage::v2::QueryWriteStatusResponse{};
              response.mutable_resource()->set_bucket(
                  "projects/_/buckets/test-bucket");
              response.mutable_resource()->set_name("test-object");
              response.mutable_resource()->set_generation(123456);
              return make_status_or(response);
            });
          });
  EXPECT_CALL(*mock, AsyncBidiWriteObject).Times(0);

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->StartUnbufferedUpload(
      {storage_experimental::ResumableUploadRequest("test-bucket",
                                                    "test-object")
           .set_multiple_options(
               storage::UseResumableUploadSession("test-upload-id")),
       connection->options()});

  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "QueryWriteStatus(1)");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "QueryWriteStatus(2)");
  next.first.set_value(true);

  auto r = pending.get();
  ASSERT_STATUS_OK(r);
  auto writer = *std::move(r);
  EXPECT_EQ(writer->UploadId(), "test-upload-id");
  ASSERT_TRUE(absl::holds_alternative<storage::ObjectMetadata>(
      writer->PersistedState()));
  auto metadata = absl::get<storage::ObjectMetadata>(writer->PersistedState());
  EXPECT_EQ(metadata.bucket(), "test-bucket");
  EXPECT_EQ(metadata.name(), "test-object");
  EXPECT_EQ(metadata.generation(), 123456);

  writer.reset();
}

TEST_F(AsyncConnectionImplTest,
       UnbufferedUploadTooManyTransientsOnStartResumableWrite) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncStartResumableWrite).Times(3).WillRepeatedly([&] {
    return sequencer.PushBack("StartResumableWrite").then([](auto) {
      return StatusOr<google::storage::v2::StartResumableWriteResponse>(
          TransientError());
    });
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->StartUnbufferedUpload(
      {storage_experimental::ResumableUploadRequest("test-bucket",
                                                    "test-object"),
       connection->options()});

  for (int i = 0; i != 3; ++i) {
    auto next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "StartResumableWrite");
    next.first.set_value(false);
  }

  auto r = pending.get();
  EXPECT_THAT(r, StatusIs(TransientError().code()));
}

TEST_F(AsyncConnectionImplTest,
       UnbufferedUploadPermanentErrorOnStartResumableWrite) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncStartResumableWrite).WillOnce([&] {
    return sequencer.PushBack("StartResumableWrite").then([](auto) {
      return StatusOr<google::storage::v2::StartResumableWriteResponse>(
          PermanentError());
    });
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->StartUnbufferedUpload(
      {storage_experimental::ResumableUploadRequest("test-bucket",
                                                    "test-object"),
       connection->options()});

  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "StartResumableWrite");
  next.first.set_value(false);

  auto r = pending.get();
  EXPECT_THAT(r, StatusIs(PermanentError().code()));
}

TEST_F(AsyncConnectionImplTest, UnbufferedUploadInvalidRequest) {
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncStartResumableWrite).Times(0);

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  // Intentionally create an invalid key. Converting this key to a proto message
  // will fail, and that should result in a
  auto key = storage::EncryptionDataFromBinaryKey("123");
  key.sha256 = "not-a-valid-base-64-SHA256";
  auto pending = connection->StartUnbufferedUpload(
      {storage_experimental::ResumableUploadRequest("test-bucket",
                                                    "test-object")
           .set_multiple_options(storage::EncryptionKey(key)),
       connection->options()});

  auto r = pending.get();
  EXPECT_THAT(r, StatusIs(StatusCode::kInvalidArgument));
}

TEST_F(AsyncConnectionImplTest,
       UnbufferedUploadTooManyTransientsOnQueryWriteStatus) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncQueryWriteStatus).Times(3).WillRepeatedly([&] {
    return sequencer.PushBack("QueryWriteStatus").then([](auto) {
      return StatusOr<google::storage::v2::QueryWriteStatusResponse>(
          TransientError());
    });
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->StartUnbufferedUpload(
      {storage_experimental::ResumableUploadRequest("test-bucket",
                                                    "test-object")
           .set_multiple_options(
               storage::UseResumableUploadSession("test-upload-id")),
       connection->options()});

  for (int i = 0; i != 3; ++i) {
    auto next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "QueryWriteStatus");
    next.first.set_value(false);
  }

  auto r = pending.get();
  EXPECT_THAT(r, StatusIs(TransientError().code()));
}

TEST_F(AsyncConnectionImplTest,
       UnbufferedUploadPermanentErrorOnQueryWriteStatus) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncQueryWriteStatus).WillOnce([&] {
    return sequencer.PushBack("QueryWriteStatus").then([](auto) {
      return StatusOr<google::storage::v2::QueryWriteStatusResponse>(
          PermanentError());
    });
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->StartUnbufferedUpload(
      {storage_experimental::ResumableUploadRequest("test-bucket",
                                                    "test-object")
           .set_multiple_options(
               storage::UseResumableUploadSession("test-upload-id")),
       connection->options()});

  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "QueryWriteStatus");
  next.first.set_value(false);

  auto r = pending.get();
  EXPECT_THAT(r, StatusIs(PermanentError().code()));
}

TEST_F(AsyncConnectionImplTest, UnbufferedUploadTooManyTransients) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncStartResumableWrite).WillOnce([] {
    auto response = google::storage::v2::StartResumableWriteResponse{};
    response.set_upload_id("test-upload-id");
    return make_ready_future(make_status_or(response));
  });
  EXPECT_CALL(*mock, AsyncBidiWriteObject).Times(3).WillRepeatedly([&] {
    return MakeErrorBidiWriteStream(sequencer, TransientError());
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->StartUnbufferedUpload(
      {storage_experimental::ResumableUploadRequest("test-bucket",
                                                    "test-object"),
       connection->options()});

  for (int i = 0; i != 3; ++i) {
    auto next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "Start");
    next.first.set_value(false);

    next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "Finish");
    next.first.set_value(true);
  }

  auto r = pending.get();
  EXPECT_THAT(r, StatusIs(TransientError().code()));
}

TEST_F(AsyncConnectionImplTest, UnbufferedUploadPermanentError) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncStartResumableWrite).WillOnce([] {
    auto response = google::storage::v2::StartResumableWriteResponse{};
    response.set_upload_id("test-upload-id");
    return make_ready_future(make_status_or(response));
  });
  EXPECT_CALL(*mock, AsyncBidiWriteObject).WillOnce([&] {
    return MakeErrorBidiWriteStream(sequencer, PermanentError());
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->StartUnbufferedUpload(
      {storage_experimental::ResumableUploadRequest("test-bucket",
                                                    "test-object"),
       connection->options()});

  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(false);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);

  auto r = pending.get();
  EXPECT_THAT(r, StatusIs(PermanentError().code()));
}

TEST_F(AsyncConnectionImplTest, BufferedUploadNewUpload) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncStartResumableWrite)
      .WillOnce([&] {
        return sequencer.PushBack("StartResumableWrite(1)").then([](auto) {
          return StatusOr<google::storage::v2::StartResumableWriteResponse>(
              TransientError());
        });
      })
      .WillOnce(
          [&](auto&, auto, auto,
              google::storage::v2::StartResumableWriteRequest const& request) {
            auto const& spec = request.write_object_spec();
            EXPECT_TRUE(spec.has_if_generation_match());
            EXPECT_EQ(spec.if_generation_match(), 123);
            auto const& resource = spec.resource();
            EXPECT_EQ(resource.bucket(), "projects/_/buckets/test-bucket");
            EXPECT_EQ(resource.name(), "test-object");
            EXPECT_EQ(resource.content_type(), "text/plain");

            return sequencer.PushBack("StartResumableWrite(2)").then([](auto) {
              auto response =
                  google::storage::v2::StartResumableWriteResponse{};
              response.set_upload_id("test-upload-id");
              return make_status_or(response);
            });
          });
  EXPECT_CALL(*mock, AsyncBidiWriteObject)
      .WillOnce(
          [&] { return MakeErrorBidiWriteStream(sequencer, TransientError()); })
      .WillOnce([&]() {
        auto stream = std::make_unique<MockAsyncBidiWriteObjectStream>();
        EXPECT_CALL(*stream, Start).WillOnce([&] {
          return sequencer.PushBack("Start");
        });
        EXPECT_CALL(*stream, Write)
            .WillOnce(
                [&](google::storage::v2::BidiWriteObjectRequest const& request,
                    grpc::WriteOptions wopt) {
                  EXPECT_EQ(request.upload_id(), "test-upload-id");
                  EXPECT_TRUE(request.finish_write());
                  EXPECT_TRUE(request.has_object_checksums());
                  EXPECT_TRUE(wopt.is_last_message());
                  return sequencer.PushBack("Write");
                });
        EXPECT_CALL(*stream, Read).WillOnce([&] {
          return sequencer.PushBack("Read").then([](auto) {
            auto response = google::storage::v2::BidiWriteObjectResponse{};
            response.mutable_resource()->set_bucket(
                "projects/_/buckets/test-bucket");
            response.mutable_resource()->set_name("test-object");
            response.mutable_resource()->set_generation(123456);
            return absl::make_optional(std::move(response));
          });
        });
        EXPECT_CALL(*stream, Cancel).Times(1);
        EXPECT_CALL(*stream, Finish).WillOnce([&] {
          return sequencer.PushBack("Finish").then(
              [](auto) { return Status{}; });
        });
        return std::unique_ptr<AsyncBidiWriteObjectStream>(std::move(stream));
      });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->StartBufferedUpload(
      {storage_experimental::ResumableUploadRequest("test-bucket",
                                                    "test-object")
           .set_multiple_options(
               storage::WithObjectMetadata(
                   storage::ObjectMetadata{}.set_content_type("text/plain")),
               storage::IfGenerationMatch(123)),
       connection->options()});

  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "StartResumableWrite(1)");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "StartResumableWrite(2)");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(false);  // The first stream fails

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(false);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(true);

  auto r = pending.get();
  ASSERT_STATUS_OK(r);
  auto writer = *std::move(r);
  EXPECT_EQ(writer->UploadId(), "test-upload-id");
  EXPECT_EQ(absl::get<std::int64_t>(writer->PersistedState()), 0);

  auto w1 = writer->Finalize({});
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Write");
  next.first.set_value(true);
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  next.first.set_value(true);

  auto response = w1.get();
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(response->bucket(), "test-bucket");
  EXPECT_EQ(response->name(), "test-object");
  EXPECT_EQ(response->generation(), 123456);

  writer.reset();
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);
}

TEST_F(AsyncConnectionImplTest, BufferedUploadNewUploadResume) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncStartResumableWrite)
      .WillOnce([&] {
        return sequencer.PushBack("StartResumableWrite(1)").then([](auto) {
          return StatusOr<google::storage::v2::StartResumableWriteResponse>(
              TransientError());
        });
      })
      .WillOnce(
          [&](auto&, auto, auto,
              google::storage::v2::StartResumableWriteRequest const& request) {
            auto const& spec = request.write_object_spec();
            EXPECT_TRUE(spec.has_if_generation_match());
            EXPECT_EQ(spec.if_generation_match(), 123);
            auto const& resource = spec.resource();
            EXPECT_EQ(resource.bucket(), "projects/_/buckets/test-bucket");
            EXPECT_EQ(resource.name(), "test-object");
            EXPECT_EQ(resource.content_type(), "text/plain");

            return sequencer.PushBack("StartResumableWrite(2)").then([](auto) {
              auto response =
                  google::storage::v2::StartResumableWriteResponse{};
              response.set_upload_id("test-upload-id");
              return make_status_or(response);
            });
          });
  EXPECT_CALL(*mock, AsyncQueryWriteStatus)
      .WillOnce([&] {
        return sequencer.PushBack("QueryWriteStatus(1)").then([](auto) {
          return StatusOr<google::storage::v2::QueryWriteStatusResponse>(
              TransientError());
        });
      })
      .WillOnce(
          [&](auto&, auto, auto,
              google::storage::v2::QueryWriteStatusRequest const& request) {
            EXPECT_EQ(request.upload_id(), "test-upload-id");

            return sequencer.PushBack("QueryWriteStatus(2)").then([](auto) {
              auto response = google::storage::v2::QueryWriteStatusResponse{};
              response.set_persisted_size(0);
              return make_status_or(response);
            });
          });
  EXPECT_CALL(*mock, AsyncBidiWriteObject)
      .WillOnce(
          [&] { return MakeErrorBidiWriteStream(sequencer, TransientError()); })
      .WillOnce([&]() {
        auto stream = std::make_unique<MockAsyncBidiWriteObjectStream>();
        EXPECT_CALL(*stream, Start).WillOnce([&] {
          return sequencer.PushBack("Start(1)");
        });
        EXPECT_CALL(*stream, Write)
            .WillOnce(
                [&](google::storage::v2::BidiWriteObjectRequest const& request,
                    grpc::WriteOptions wopt) {
                  EXPECT_EQ(request.upload_id(), "test-upload-id");
                  EXPECT_TRUE(request.finish_write());
                  EXPECT_TRUE(request.has_object_checksums());
                  EXPECT_TRUE(wopt.is_last_message());
                  return sequencer.PushBack("Write");
                });
        EXPECT_CALL(*stream, Read).WillOnce([&] {
          return sequencer.PushBack("Read").then([](auto) {
            return absl::optional<
                google::storage::v2::BidiWriteObjectResponse>{};
          });
        });
        EXPECT_CALL(*stream, Cancel).Times(1);
        EXPECT_CALL(*stream, Finish).WillOnce([&] {
          return sequencer.PushBack("Finish").then(
              [](auto) { return TransientError(); });
        });
        return std::unique_ptr<AsyncBidiWriteObjectStream>(std::move(stream));
      })
      .WillOnce([&]() {
        auto stream = std::make_unique<MockAsyncBidiWriteObjectStream>();
        EXPECT_CALL(*stream, Start).WillOnce([&] {
          return sequencer.PushBack("Start(2)");
        });
        EXPECT_CALL(*stream, Write)
            .WillOnce(
                [&](google::storage::v2::BidiWriteObjectRequest const& request,
                    grpc::WriteOptions wopt) {
                  EXPECT_EQ(request.upload_id(), "test-upload-id");
                  EXPECT_TRUE(request.finish_write());
                  EXPECT_TRUE(request.has_object_checksums());
                  EXPECT_TRUE(wopt.is_last_message());
                  return sequencer.PushBack("Write");
                });
        EXPECT_CALL(*stream, Read).WillOnce([&] {
          return sequencer.PushBack("Read").then([](auto) {
            auto response = google::storage::v2::BidiWriteObjectResponse{};
            response.mutable_resource()->set_bucket(
                "projects/_/buckets/test-bucket");
            response.mutable_resource()->set_name("test-object");
            response.mutable_resource()->set_generation(123456);
            return absl::make_optional(std::move(response));
          });
        });
        EXPECT_CALL(*stream, Cancel).Times(1);
        EXPECT_CALL(*stream, Finish).WillOnce([&] {
          return sequencer.PushBack("Finish").then(
              [](auto) { return Status{}; });
        });
        return std::unique_ptr<AsyncBidiWriteObjectStream>(std::move(stream));
      });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->StartBufferedUpload(
      {storage_experimental::ResumableUploadRequest("test-bucket",
                                                    "test-object")
           .set_multiple_options(
               storage::WithObjectMetadata(
                   storage::ObjectMetadata{}.set_content_type("text/plain")),
               storage::IfGenerationMatch(123)),
       connection->options()});

  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "StartResumableWrite(1)");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "StartResumableWrite(2)");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start");
  next.first.set_value(false);  // The first stream fails

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(false);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start(1)");
  next.first.set_value(true);

  auto r = pending.get();
  ASSERT_STATUS_OK(r);
  auto writer = *std::move(r);
  EXPECT_EQ(writer->UploadId(), "test-upload-id");
  EXPECT_EQ(absl::get<std::int64_t>(writer->PersistedState()), 0);

  auto w1 = writer->Finalize({});
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Write");
  next.first.set_value(true);
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "QueryWriteStatus(1)");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "QueryWriteStatus(2)");
  next.first.set_value(true);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Start(2)");
  next.first.set_value(true);
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Write");
  next.first.set_value(true);
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Read");
  next.first.set_value(true);

  auto response = w1.get();
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(response->bucket(), "test-bucket");
  EXPECT_EQ(response->name(), "test-object");
  EXPECT_EQ(response->generation(), 123456);

  writer.reset();
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);
}

TEST_F(AsyncConnectionImplTest, DeleteObject) {
  auto constexpr kRequestText = R"pb(
    bucket: "invalid-test-only"
    object: "test-object"
    generation: 12345
    if_metageneration_match: 42
  )pb";
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncDeleteObject)
      .WillOnce([&] {
        return sequencer.PushBack("DeleteObject(1)").then([](auto) {
          return TransientError();
        });
      })
      .WillOnce([&](CompletionQueue&, auto,
                    google::cloud::internal::ImmutableOptions const& options,
                    google::storage::v2::DeleteObjectRequest const& request) {
        // Verify at least one option is initialized with the correct values.
        EXPECT_EQ(options->get<AuthorityOption>(), kAuthority);
        google::storage::v2::DeleteObjectRequest expected;
        EXPECT_TRUE(TextFormat::ParseFromString(kRequestText, &expected));
        EXPECT_THAT(request, IsProtoEqual(expected));
        return sequencer.PushBack("DeleteObject(2)").then([](auto) {
          return Status{};
        });
      });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  google::storage::v2::DeleteObjectRequest request;
  EXPECT_TRUE(TextFormat::ParseFromString(kRequestText, &request));
  auto pending =
      connection->DeleteObject({std::move(request), connection->options()});

  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "DeleteObject(1)");
  next.first.set_value(false);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "DeleteObject(2)");
  next.first.set_value(true);

  auto response = pending.get();
  ASSERT_STATUS_OK(response);
}

TEST_F(AsyncConnectionImplTest, DeleteObjectPermanentError) {
  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncDeleteObject).WillOnce([&] {
    return sequencer.PushBack("DeleteObject").then([](auto) {
      return PermanentError();
    });
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto pending = connection->DeleteObject(
      {google::storage::v2::DeleteObjectRequest{}, connection->options()});

  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "DeleteObject");
  next.first.set_value(false);

  auto response = pending.get();
  EXPECT_THAT(response, StatusIs(PermanentError().code()));
}

TEST_F(AsyncConnectionImplTest, AsyncDeleteObjectTooManyTransients) {
  auto constexpr kRequestText =
      R"pb(
    bucket: "invalid-test-only" object: "test-object" generation: 12345
      )pb";

  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncDeleteObject).Times(3).WillRepeatedly([&] {
    return sequencer.PushBack("DeleteObject").then([](auto) {
      return TransientError();
    });
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  google::storage::v2::DeleteObjectRequest request;
  EXPECT_TRUE(TextFormat::ParseFromString(kRequestText, &request));
  auto pending =
      connection->DeleteObject({std::move(request), connection->options()});

  for (int i = 0; i != 3; ++i) {
    auto next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "DeleteObject");
    next.first.set_value(false);
  }

  auto response = pending.get();
  EXPECT_THAT(response, StatusIs(TransientError().code()));
}

// For RewriteObject just validate the basic functionality. The tests for
// `RewriterConnectionImpl` are the important ones.
TEST_F(AsyncConnectionImplTest, RewriteObject) {
  using ::google::storage::v2::RewriteObjectRequest;
  using ::google::storage::v2::RewriteResponse;

  AsyncSequencer<bool> sequencer;
  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncRewriteObject)
      .WillOnce([&] {
        return sequencer.PushBack("RewriteObject(1)").then([](auto) {
          return StatusOr<google::storage::v2::RewriteResponse>(
              TransientError());
        });
      })
      .WillOnce([&] {
        return sequencer.PushBack("RewriteObject(2)").then([](auto) {
          google::storage::v2::RewriteResponse response;
          response.set_total_bytes_rewritten(1000);
          response.set_object_size(3000);
          response.set_rewrite_token("test-rewrite-token");
          return make_status_or(response);
        });
      });

  auto match_progress = [](int rewritten, int size) {
    return AllOf(
        ResultOf(
            "total bytes",
            [](RewriteResponse const& v) { return v.total_bytes_rewritten(); },
            rewritten),
        ResultOf(
            "size", [](RewriteResponse const& v) { return v.object_size(); },
            size),
        ResultOf(
            "token", [](RewriteResponse const& v) { return v.rewrite_token(); },
            "test-rewrite-token"));
  };

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  auto connection = MakeTestConnection(pool.cq(), mock);
  auto rewriter = connection->RewriteObject(
      {RewriteObjectRequest{}, connection->options()});

  auto r1 = rewriter->Iterate();
  auto next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "RewriteObject(1)");
  next.first.set_value(true);
  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "RewriteObject(2)");
  next.first.set_value(true);
  EXPECT_THAT(r1.get(), IsOkAndHolds(match_progress(1000, 3000)));
}

TEST_F(AsyncConnectionImplTest, MakeReaderConnectionFactory) {
  AsyncSequencer<bool> sequencer;
  auto make_success_stream = [&](AsyncSequencer<bool>& sequencer) {
    auto stream = std::make_unique<MockAsyncObjectMediaStream>();
    EXPECT_CALL(*stream, Start).WillOnce([&] {
      return sequencer.PushBack("Start");
    });
    EXPECT_CALL(*stream, Read).WillOnce([&] {
      return sequencer.PushBack("Read").then([](auto) {
        return absl::optional<google::storage::v2::ReadObjectResponse>{};
      });
    });
    EXPECT_CALL(*stream, Finish).WillOnce([&] {
      return sequencer.PushBack("Finish").then([](auto) { return Status{}; });
    });
    return std::unique_ptr<AsyncReadObjectStream>(std::move(stream));
  };
  auto verify_empty_stream = [](AsyncSequencer<bool>& sequencer, auto pending) {
    // First simulate a failed `ReadObject()`. This returns a streaming RPC
    // that completes with `false` on `Start()` (i.e. never starts) and then
    // completes with a transient error on `Finish()`.
    auto next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "Start");
    next.first.set_value(false);

    next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "Finish");
    next.first.set_value(true);

    // Then simulate a successful `ReadObject()`. To simplify the test we assume
    // this returns no data. The streaming RPC completes with `true` on
    // `Start()`, then an unset optional on `Read()` (indicating 'end of the
    // streaming RPC'), and then a success `Status` for `Finish()`.
    next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "Start");
    next.first.set_value(true);

    auto r = pending.get();
    ASSERT_STATUS_OK(r);
    auto reader = *std::move(r);
    auto data = reader->Read();
    next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "Read");
    next.first.set_value(true);

    next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "Finish");
    next.first.set_value(true);

    EXPECT_THAT(data.get(), VariantWith<Status>(IsOk()));
  };

  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncReadObject)
      .WillOnce(
          [&] { return MakeErrorReadStream(sequencer, TransientError()); })
      .WillOnce([&](CompletionQueue const&,
                    std::shared_ptr<grpc::ClientContext> const& context,
                    google::cloud::internal::ImmutableOptions const& options,
                    google::storage::v2::ReadObjectRequest const& request) {
        // Verify at least one option is initialized with the correct
        // values.
        EXPECT_EQ(options->get<AuthorityOption>(), kAuthority);
        auto metadata = GetMetadata(*context);
        EXPECT_THAT(metadata, UnorderedElementsAre(
                                  Pair("x-goog-quota-user", "test-quota-user"),
                                  Pair("x-goog-fieldmask", "field1,field2")));
        EXPECT_THAT(request.bucket(), "projects/_/buckets/test-bucket");
        EXPECT_THAT(request.object(), "test-object");
        EXPECT_THAT(request.read_offset(), 1000);
        EXPECT_THAT(request.read_limit(), 1000);
        return make_success_stream(sequencer);
      })
      .WillOnce(
          [&] { return MakeErrorReadStream(sequencer, TransientError()); })
      .WillOnce([&](CompletionQueue const&,
                    std::shared_ptr<grpc::ClientContext> const& context,
                    google::cloud::internal::ImmutableOptions const& options,
                    google::storage::v2::ReadObjectRequest const& request) {
        // Verify at least one option is initialized with the correct
        // values.
        EXPECT_EQ(options->get<AuthorityOption>(), kAuthority);
        auto metadata = GetMetadata(*context);
        EXPECT_THAT(metadata, UnorderedElementsAre(
                                  Pair("x-goog-quota-user", "test-quota-user"),
                                  Pair("x-goog-fieldmask", "field1,field2")));
        EXPECT_THAT(request.bucket(), "projects/_/buckets/test-bucket");
        EXPECT_THAT(request.object(), "test-object");
        EXPECT_THAT(request.generation(), 1234);
        EXPECT_THAT(request.read_offset(), 1500);
        EXPECT_THAT(request.read_limit(), 500);
        return make_success_stream(sequencer);
      });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  AsyncConnectionImpl connection(
      pool.cq(), std::shared_ptr<GrpcChannelRefresh>{}, mock, TestOptions());
  auto request =
      storage_experimental::ReadObjectRequest("test-bucket", "test-object")
          .set_multiple_options(storage::ReadRange(1000, 2000),
                                storage::Fields("field1,field2"),
                                storage::QuotaUser("test-quota-user"));
  google::storage::v2::ReadObjectRequest proto_request;
  EXPECT_TRUE(TextFormat::ParseFromString(
      R"pb(
        bucket: "projects/_/buckets/test-bucket"
        object: "test-object"
        read_offset: 1000
        read_limit: 1000
      )pb",
      &proto_request));

  auto hash_function = std::make_shared<MockHashFunction>();
  auto factory = connection.MakeReaderConnectionFactory(
      internal::MakeImmutableOptions(connection.options()), request,
      proto_request, std::move(hash_function));

  // Verify the factory makes the expected request and consume the output
  verify_empty_stream(sequencer, factory(storage::Generation(), 0));

  verify_empty_stream(sequencer, factory(storage::Generation(1234), 500));
}

TEST_F(AsyncConnectionImplTest, MakeReaderConnectionFactoryPermanentError) {
  AsyncSequencer<bool> sequencer;

  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncReadObject).WillOnce([&] {
    return MakeErrorReadStream(sequencer, PermanentError());
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  AsyncConnectionImpl connection(
      pool.cq(), std::shared_ptr<GrpcChannelRefresh>{}, mock, TestOptions());
  auto request =
      storage_experimental::ReadObjectRequest("test-bucket", "test-object")
          .set_multiple_options(storage::ReadRange(1000, 2000),
                                storage::Fields("field1,field2"),
                                storage::QuotaUser("test-quota-user"));
  google::storage::v2::ReadObjectRequest proto_request;
  EXPECT_TRUE(TextFormat::ParseFromString(
      R"pb(
        bucket: "projects/_/buckets/test-bucket"
        object: "test-object"
        read_offset: 1000
        read_limit: 1000
      )pb",
      &proto_request));

  auto hash_function = std::make_shared<MockHashFunction>();
  auto factory = connection.MakeReaderConnectionFactory(
      internal::MakeImmutableOptions(connection.options()), request,
      proto_request, hash_function);

  // Verify the factory makes the expected request.
  auto pending = factory(storage::Generation(), 0);

  auto next = sequencer.PopFrontWithName();
  next.first.set_value(false);

  next = sequencer.PopFrontWithName();
  EXPECT_EQ(next.second, "Finish");
  next.first.set_value(true);

  auto r = pending.get();
  EXPECT_THAT(r, StatusIs(PermanentError().code()));
}

TEST_F(AsyncConnectionImplTest, MakeReaderConnectionFactoryTooManyTransients) {
  AsyncSequencer<bool> sequencer;

  auto mock = std::make_shared<storage::testing::MockStorageStub>();
  EXPECT_CALL(*mock, AsyncReadObject).Times(3).WillRepeatedly([&] {
    return MakeErrorReadStream(sequencer, TransientError());
  });

  internal::AutomaticallyCreatedBackgroundThreads pool(1);
  AsyncConnectionImpl connection(
      pool.cq(), std::shared_ptr<GrpcChannelRefresh>{}, mock, TestOptions());
  auto request =
      storage_experimental::ReadObjectRequest("test-bucket", "test-object")
          .set_multiple_options(storage::ReadRange(1000, 2000),
                                storage::Fields("field1,field2"),
                                storage::QuotaUser("test-quota-user"));
  google::storage::v2::ReadObjectRequest proto_request;
  EXPECT_TRUE(TextFormat::ParseFromString(
      R"pb(
        bucket: "projects/_/buckets/test-bucket"
        object: "test-object"
        read_offset: 1000
        read_limit: 1000
      )pb",
      &proto_request));

  auto hash_function = std::make_shared<MockHashFunction>();
  auto factory = connection.MakeReaderConnectionFactory(
      internal::MakeImmutableOptions(connection.options()), request,
      proto_request, hash_function);
  // Verify the factory makes the expected request.
  auto pending = factory(storage::Generation(), 0);

  for (int i = 0; i != 3; ++i) {
    auto next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "Start");
    next.first.set_value(false);

    next = sequencer.PopFrontWithName();
    EXPECT_EQ(next.second, "Finish");
    next.first.set_value(true);
  }

  auto r = pending.get();
  EXPECT_THAT(r, StatusIs(TransientError().code()));
}

}  // namespace
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace storage_internal
}  // namespace cloud
}  // namespace google
