// Copyright 2022 Google LLC
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
// source: google/cloud/dialogflow/v2/session_entity_type.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DIALOGFLOW_ES_SESSION_ENTITY_TYPES_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DIALOGFLOW_ES_SESSION_ENTITY_TYPES_CONNECTION_H

#include "google/cloud/dialogflow_es/internal/session_entity_types_retry_traits.h"
#include "google/cloud/dialogflow_es/internal/session_entity_types_stub.h"
#include "google/cloud/dialogflow_es/session_entity_types_connection_idempotency_policy.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace dialogflow_es {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using SessionEntityTypesRetryPolicy =
    ::google::cloud::internal::TraitBasedRetryPolicy<
        dialogflow_es_internal::SessionEntityTypesRetryTraits>;

using SessionEntityTypesLimitedTimeRetryPolicy =
    ::google::cloud::internal::LimitedTimeRetryPolicy<
        dialogflow_es_internal::SessionEntityTypesRetryTraits>;

using SessionEntityTypesLimitedErrorCountRetryPolicy =
    ::google::cloud::internal::LimitedErrorCountRetryPolicy<
        dialogflow_es_internal::SessionEntityTypesRetryTraits>;

/**
 * The `SessionEntityTypesConnection` object for `SessionEntityTypesClient`.
 *
 * This interface defines virtual methods for each of the user-facing overload
 * sets in `SessionEntityTypesClient`. This allows users to inject custom
 * behavior (e.g., with a Google Mock object) when writing tests that use
 * objects of type `SessionEntityTypesClient`.
 *
 * To create a concrete instance, see `MakeSessionEntityTypesConnection()`.
 *
 * For mocking, see `dialogflow_es_mocks::MockSessionEntityTypesConnection`.
 */
class SessionEntityTypesConnection {
 public:
  virtual ~SessionEntityTypesConnection() = 0;

  virtual Options options() { return Options{}; }

  virtual StreamRange<google::cloud::dialogflow::v2::SessionEntityType>
  ListSessionEntityTypes(
      google::cloud::dialogflow::v2::ListSessionEntityTypesRequest request);

  virtual StatusOr<google::cloud::dialogflow::v2::SessionEntityType>
  GetSessionEntityType(
      google::cloud::dialogflow::v2::GetSessionEntityTypeRequest const&
          request);

  virtual StatusOr<google::cloud::dialogflow::v2::SessionEntityType>
  CreateSessionEntityType(
      google::cloud::dialogflow::v2::CreateSessionEntityTypeRequest const&
          request);

  virtual StatusOr<google::cloud::dialogflow::v2::SessionEntityType>
  UpdateSessionEntityType(
      google::cloud::dialogflow::v2::UpdateSessionEntityTypeRequest const&
          request);

  virtual Status DeleteSessionEntityType(
      google::cloud::dialogflow::v2::DeleteSessionEntityTypeRequest const&
          request);
};

/**
 * A factory function to construct an object of type
 * `SessionEntityTypesConnection`.
 *
 * The returned connection object should not be used directly; instead it
 * should be passed as an argument to the constructor of
 * SessionEntityTypesClient, and that class used instead.
 *
 * The optional @p opts argument may be used to configure aspects of the
 * returned `SessionEntityTypesConnection`. Expected options are any of the
 * types in the following option lists:
 *
 * - `google::cloud::CommonOptionList`
 * - `google::cloud::GrpcOptionList`
 * - `google::cloud::dialogflow_es::SessionEntityTypesPolicyOptionList`
 *
 * @note Unrecognized options will be ignored. To debug issues with options set
 *     `GOOGLE_CLOUD_CPP_ENABLE_CLOG=yes` in the environment and unexpected
 *     options will be logged.
 *
 * @param options (optional) Configure the `SessionEntityTypesConnection`
 * created by this function.
 */
std::shared_ptr<SessionEntityTypesConnection> MakeSessionEntityTypesConnection(
    Options options = {});

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dialogflow_es
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace dialogflow_es_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<dialogflow_es::SessionEntityTypesConnection>
MakeSessionEntityTypesConnection(std::shared_ptr<SessionEntityTypesStub> stub,
                                 Options options);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dialogflow_es_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DIALOGFLOW_ES_SESSION_ENTITY_TYPES_CONNECTION_H
