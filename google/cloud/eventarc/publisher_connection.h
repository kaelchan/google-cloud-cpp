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
// source: google/cloud/eventarc/publishing/v1/publisher.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_EVENTARC_PUBLISHER_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_EVENTARC_PUBLISHER_CONNECTION_H

#include "google/cloud/eventarc/internal/publisher_retry_traits.h"
#include "google/cloud/eventarc/internal/publisher_stub.h"
#include "google/cloud/eventarc/publisher_connection_idempotency_policy.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace eventarc {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using PublisherRetryPolicy = ::google::cloud::internal::TraitBasedRetryPolicy<
    eventarc_internal::PublisherRetryTraits>;

using PublisherLimitedTimeRetryPolicy =
    ::google::cloud::internal::LimitedTimeRetryPolicy<
        eventarc_internal::PublisherRetryTraits>;

using PublisherLimitedErrorCountRetryPolicy =
    ::google::cloud::internal::LimitedErrorCountRetryPolicy<
        eventarc_internal::PublisherRetryTraits>;

/**
 * The `PublisherConnection` object for `PublisherClient`.
 *
 * This interface defines virtual methods for each of the user-facing overload
 * sets in `PublisherClient`. This allows users to inject custom behavior
 * (e.g., with a Google Mock object) when writing tests that use objects of type
 * `PublisherClient`.
 *
 * To create a concrete instance, see `MakePublisherConnection()`.
 *
 * For mocking, see `eventarc_mocks::MockPublisherConnection`.
 */
class PublisherConnection {
 public:
  virtual ~PublisherConnection() = 0;

  virtual Options options() { return Options{}; }

  virtual StatusOr<google::cloud::eventarc::publishing::v1::
                       PublishChannelConnectionEventsResponse>
  PublishChannelConnectionEvents(
      google::cloud::eventarc::publishing::v1::
          PublishChannelConnectionEventsRequest const& request);

  virtual StatusOr<
      google::cloud::eventarc::publishing::v1::PublishEventsResponse>
  PublishEvents(
      google::cloud::eventarc::publishing::v1::PublishEventsRequest const&
          request);
};

/**
 * A factory function to construct an object of type `PublisherConnection`.
 *
 * The returned connection object should not be used directly; instead it
 * should be passed as an argument to the constructor of PublisherClient,
 * and that class used instead.
 *
 * The optional @p opts argument may be used to configure aspects of the
 * returned `PublisherConnection`. Expected options are any of the types in
 * the following option lists:
 *
 * - `google::cloud::CommonOptionList`
 * - `google::cloud::GrpcOptionList`
 * - `google::cloud::eventarc::PublisherPolicyOptionList`
 *
 * @note Unrecognized options will be ignored. To debug issues with options set
 *     `GOOGLE_CLOUD_CPP_ENABLE_CLOG=yes` in the environment and unexpected
 *     options will be logged.
 *
 * @param options (optional) Configure the `PublisherConnection` created by
 * this function.
 */
std::shared_ptr<PublisherConnection> MakePublisherConnection(
    Options options = {});

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace eventarc
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace eventarc_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<eventarc::PublisherConnection> MakePublisherConnection(
    std::shared_ptr<PublisherStub> stub, Options options);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace eventarc_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_EVENTARC_PUBLISHER_CONNECTION_H
