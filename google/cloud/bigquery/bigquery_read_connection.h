// Copyright 2021 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: google/cloud/bigquery/storage/v1/storage.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGQUERY_BIGQUERY_READ_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGQUERY_BIGQUERY_READ_CONNECTION_H

#include "google/cloud/bigquery/bigquery_read_connection_idempotency_policy.h"
#include "google/cloud/bigquery/internal/bigquery_read_retry_traits.h"
#include "google/cloud/bigquery/internal/bigquery_read_stub.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace bigquery {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using BigQueryReadRetryPolicy =
    ::google::cloud::internal::TraitBasedRetryPolicy<
        bigquery_internal::BigQueryReadRetryTraits>;

using BigQueryReadLimitedTimeRetryPolicy =
    ::google::cloud::internal::LimitedTimeRetryPolicy<
        bigquery_internal::BigQueryReadRetryTraits>;

using BigQueryReadLimitedErrorCountRetryPolicy =
    ::google::cloud::internal::LimitedErrorCountRetryPolicy<
        bigquery_internal::BigQueryReadRetryTraits>;

GOOGLE_CLOUD_CPP_DEPRECATED(
    "applications should not need this."
    " Please file a bug at https://github.com/googleapis/google-cloud-cpp"
    " if you do.")
void BigQueryReadReadRowsStreamingUpdater(
    google::cloud::bigquery::storage::v1::ReadRowsResponse const& response,
    google::cloud::bigquery::storage::v1::ReadRowsRequest& request);

/**
 * The `BigQueryReadConnection` object for `BigQueryReadClient`.
 *
 * This interface defines virtual methods for each of the user-facing overload
 * sets in `BigQueryReadClient`. This allows users to inject custom behavior
 * (e.g., with a Google Mock object) when writing tests that use objects of type
 * `BigQueryReadClient`.
 *
 * To create a concrete instance, see `MakeBigQueryReadConnection()`.
 *
 * For mocking, see `bigquery_mocks::MockBigQueryReadConnection`.
 */
class BigQueryReadConnection {
 public:
  virtual ~BigQueryReadConnection() = 0;

  virtual Options options() { return Options{}; }

  virtual StatusOr<google::cloud::bigquery::storage::v1::ReadSession>
  CreateReadSession(
      google::cloud::bigquery::storage::v1::CreateReadSessionRequest const&
          request);

  virtual StreamRange<google::cloud::bigquery::storage::v1::ReadRowsResponse>
  ReadRows(
      google::cloud::bigquery::storage::v1::ReadRowsRequest const& request);

  virtual StatusOr<
      google::cloud::bigquery::storage::v1::SplitReadStreamResponse>
  SplitReadStream(
      google::cloud::bigquery::storage::v1::SplitReadStreamRequest const&
          request);
};

/**
 * A factory function to construct an object of type `BigQueryReadConnection`.
 *
 * The returned connection object should not be used directly; instead it
 * should be passed as an argument to the constructor of BigQueryReadClient,
 * and that class used instead.
 *
 * The optional @p opts argument may be used to configure aspects of the
 * returned `BigQueryReadConnection`. Expected options are any of the types in
 * the following option lists:
 *
 * - `google::cloud::CommonOptionList`
 * - `google::cloud::GrpcOptionList`
 * - `google::cloud::bigquery::BigQueryReadPolicyOptionList`
 *
 * @note Unrecognized options will be ignored. To debug issues with options set
 *     `GOOGLE_CLOUD_CPP_ENABLE_CLOG=yes` in the environment and unexpected
 *     options will be logged.
 *
 * @param options (optional) Configure the `BigQueryReadConnection` created by
 * this function.
 */
std::shared_ptr<BigQueryReadConnection> MakeBigQueryReadConnection(
    Options options = {});

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
namespace gcpcxxV1 = GOOGLE_CLOUD_CPP_NS;  // NOLINT(misc-unused-alias-decls)
}  // namespace bigquery
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace bigquery_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<bigquery::BigQueryReadConnection> MakeBigQueryReadConnection(
    std::shared_ptr<BigQueryReadStub> stub, Options options);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
namespace gcpcxxV1 = GOOGLE_CLOUD_CPP_NS;  // NOLINT(misc-unused-alias-decls)
}  // namespace bigquery_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGQUERY_BIGQUERY_READ_CONNECTION_H
