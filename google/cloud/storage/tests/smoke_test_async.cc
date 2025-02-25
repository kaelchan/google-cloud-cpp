// Copyright 2024 Google LLC
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

#if GOOGLE_CLOUD_CPP_STORAGE_HAVE_GRPC

#include "google/cloud/storage/async/bucket_name.h"
#include "google/cloud/storage/async/client.h"
#include "google/cloud/storage/testing/random_names.h"
#include "google/cloud/internal/getenv.h"
#include "google/cloud/internal/random.h"
#include "google/cloud/testing_util/status_matchers.h"
#include <gmock/gmock.h>
#include <tuple>
#include <utility>

namespace google {
namespace cloud {
namespace storage_experimental {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

using ::google::cloud::internal::GetEnv;

TEST(SmokeTest, Grpc) {
  auto const bucket_name =
      GetEnv("GOOGLE_CLOUD_CPP_STORAGE_TEST_BUCKET_NAME").value_or("");
  if (bucket_name.empty()) GTEST_SKIP();

  auto client = google::cloud::storage_experimental::AsyncClient();
  auto gen = google::cloud::internal::MakeDefaultPRNG();
  auto object_name = google::cloud::storage::testing::MakeRandomObjectName(gen);

  auto insert = client
                    .InsertObject(bucket_name, object_name, "Hello World!",
                                  storage::IfGenerationMatch(0))
                    .get();
  ASSERT_STATUS_OK(insert);
  auto metadata = *insert;

  auto payload =
      client
          .ReadObjectRange(bucket_name, metadata.name(), 0, 1024,
                           storage::Generation(metadata.generation()))
          .get();
  ASSERT_STATUS_OK(payload);
  std::string contents;
  for (auto v : payload->contents()) contents += std::string(v);
  EXPECT_EQ(contents, "Hello World!");

  auto deleted = client
                     .DeleteObject(BucketName(metadata.bucket()),
                                   metadata.name(), metadata.generation())
                     .get();
  EXPECT_STATUS_OK(deleted);
}

}  // namespace
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace storage_experimental
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_STORAGE_HAVE_GRPC
