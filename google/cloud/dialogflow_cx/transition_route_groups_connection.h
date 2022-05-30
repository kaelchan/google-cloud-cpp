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
// source: google/cloud/dialogflow/cx/v3/transition_route_group.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DIALOGFLOW_CX_TRANSITION_ROUTE_GROUPS_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DIALOGFLOW_CX_TRANSITION_ROUTE_GROUPS_CONNECTION_H

#include "google/cloud/dialogflow_cx/internal/transition_route_groups_retry_traits.h"
#include "google/cloud/dialogflow_cx/internal/transition_route_groups_stub.h"
#include "google/cloud/dialogflow_cx/transition_route_groups_connection_idempotency_policy.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace dialogflow_cx {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using TransitionRouteGroupsRetryPolicy =
    ::google::cloud::internal::TraitBasedRetryPolicy<
        dialogflow_cx_internal::TransitionRouteGroupsRetryTraits>;

using TransitionRouteGroupsLimitedTimeRetryPolicy =
    ::google::cloud::internal::LimitedTimeRetryPolicy<
        dialogflow_cx_internal::TransitionRouteGroupsRetryTraits>;

using TransitionRouteGroupsLimitedErrorCountRetryPolicy =
    ::google::cloud::internal::LimitedErrorCountRetryPolicy<
        dialogflow_cx_internal::TransitionRouteGroupsRetryTraits>;

/**
 * The `TransitionRouteGroupsConnection` object for
 * `TransitionRouteGroupsClient`.
 *
 * This interface defines virtual methods for each of the user-facing overload
 * sets in `TransitionRouteGroupsClient`. This allows users to inject custom
 * behavior (e.g., with a Google Mock object) when writing tests that use
 * objects of type `TransitionRouteGroupsClient`.
 *
 * To create a concrete instance, see `MakeTransitionRouteGroupsConnection()`.
 *
 * For mocking, see `dialogflow_cx_mocks::MockTransitionRouteGroupsConnection`.
 */
class TransitionRouteGroupsConnection {
 public:
  virtual ~TransitionRouteGroupsConnection() = 0;

  virtual Options options() { return Options{}; }

  virtual StreamRange<google::cloud::dialogflow::cx::v3::TransitionRouteGroup>
  ListTransitionRouteGroups(
      google::cloud::dialogflow::cx::v3::ListTransitionRouteGroupsRequest
          request);

  virtual StatusOr<google::cloud::dialogflow::cx::v3::TransitionRouteGroup>
  GetTransitionRouteGroup(
      google::cloud::dialogflow::cx::v3::GetTransitionRouteGroupRequest const&
          request);

  virtual StatusOr<google::cloud::dialogflow::cx::v3::TransitionRouteGroup>
  CreateTransitionRouteGroup(
      google::cloud::dialogflow::cx::v3::
          CreateTransitionRouteGroupRequest const& request);

  virtual StatusOr<google::cloud::dialogflow::cx::v3::TransitionRouteGroup>
  UpdateTransitionRouteGroup(
      google::cloud::dialogflow::cx::v3::
          UpdateTransitionRouteGroupRequest const& request);

  virtual Status DeleteTransitionRouteGroup(
      google::cloud::dialogflow::cx::v3::
          DeleteTransitionRouteGroupRequest const& request);
};

/**
 * A factory function to construct an object of type
 * `TransitionRouteGroupsConnection`.
 *
 * The returned connection object should not be used directly; instead it
 * should be passed as an argument to the constructor of
 * TransitionRouteGroupsClient, and that class used instead.
 *
 * The optional @p opts argument may be used to configure aspects of the
 * returned `TransitionRouteGroupsConnection`. Expected options are any of the
 * types in the following option lists:
 *
 * - `google::cloud::CommonOptionList`
 * - `google::cloud::GrpcOptionList`
 * - `google::cloud::dialogflow_cx::TransitionRouteGroupsPolicyOptionList`
 *
 * @note Unrecognized options will be ignored. To debug issues with options set
 *     `GOOGLE_CLOUD_CPP_ENABLE_CLOG=yes` in the environment and unexpected
 *     options will be logged.
 *
 * @param options (optional) Configure the `TransitionRouteGroupsConnection`
 * created by this function.
 */
std::shared_ptr<TransitionRouteGroupsConnection>
MakeTransitionRouteGroupsConnection(Options options = {});

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dialogflow_cx
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace dialogflow_cx_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<dialogflow_cx::TransitionRouteGroupsConnection>
MakeTransitionRouteGroupsConnection(
    std::shared_ptr<TransitionRouteGroupsStub> stub, Options options);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dialogflow_cx_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DIALOGFLOW_CX_TRANSITION_ROUTE_GROUPS_CONNECTION_H
