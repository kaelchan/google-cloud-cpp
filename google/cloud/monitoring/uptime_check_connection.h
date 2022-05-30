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
// source: google/monitoring/v3/uptime_service.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_MONITORING_UPTIME_CHECK_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_MONITORING_UPTIME_CHECK_CONNECTION_H

#include "google/cloud/monitoring/internal/uptime_check_retry_traits.h"
#include "google/cloud/monitoring/internal/uptime_check_stub.h"
#include "google/cloud/monitoring/uptime_check_connection_idempotency_policy.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace monitoring {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using UptimeCheckServiceRetryPolicy =
    ::google::cloud::internal::TraitBasedRetryPolicy<
        monitoring_internal::UptimeCheckServiceRetryTraits>;

using UptimeCheckServiceLimitedTimeRetryPolicy =
    ::google::cloud::internal::LimitedTimeRetryPolicy<
        monitoring_internal::UptimeCheckServiceRetryTraits>;

using UptimeCheckServiceLimitedErrorCountRetryPolicy =
    ::google::cloud::internal::LimitedErrorCountRetryPolicy<
        monitoring_internal::UptimeCheckServiceRetryTraits>;

/**
 * The `UptimeCheckServiceConnection` object for `UptimeCheckServiceClient`.
 *
 * This interface defines virtual methods for each of the user-facing overload
 * sets in `UptimeCheckServiceClient`. This allows users to inject custom
 * behavior (e.g., with a Google Mock object) when writing tests that use
 * objects of type `UptimeCheckServiceClient`.
 *
 * To create a concrete instance, see `MakeUptimeCheckServiceConnection()`.
 *
 * For mocking, see `monitoring_mocks::MockUptimeCheckServiceConnection`.
 */
class UptimeCheckServiceConnection {
 public:
  virtual ~UptimeCheckServiceConnection() = 0;

  virtual Options options() { return Options{}; }

  virtual StreamRange<google::monitoring::v3::UptimeCheckConfig>
  ListUptimeCheckConfigs(
      google::monitoring::v3::ListUptimeCheckConfigsRequest request);

  virtual StatusOr<google::monitoring::v3::UptimeCheckConfig>
  GetUptimeCheckConfig(
      google::monitoring::v3::GetUptimeCheckConfigRequest const& request);

  virtual StatusOr<google::monitoring::v3::UptimeCheckConfig>
  CreateUptimeCheckConfig(
      google::monitoring::v3::CreateUptimeCheckConfigRequest const& request);

  virtual StatusOr<google::monitoring::v3::UptimeCheckConfig>
  UpdateUptimeCheckConfig(
      google::monitoring::v3::UpdateUptimeCheckConfigRequest const& request);

  virtual Status DeleteUptimeCheckConfig(
      google::monitoring::v3::DeleteUptimeCheckConfigRequest const& request);

  virtual StreamRange<google::monitoring::v3::UptimeCheckIp> ListUptimeCheckIps(
      google::monitoring::v3::ListUptimeCheckIpsRequest request);
};

/**
 * A factory function to construct an object of type
 * `UptimeCheckServiceConnection`.
 *
 * The returned connection object should not be used directly; instead it
 * should be passed as an argument to the constructor of
 * UptimeCheckServiceClient, and that class used instead.
 *
 * The optional @p opts argument may be used to configure aspects of the
 * returned `UptimeCheckServiceConnection`. Expected options are any of the
 * types in the following option lists:
 *
 * - `google::cloud::CommonOptionList`
 * - `google::cloud::GrpcOptionList`
 * - `google::cloud::monitoring::UptimeCheckServicePolicyOptionList`
 *
 * @note Unrecognized options will be ignored. To debug issues with options set
 *     `GOOGLE_CLOUD_CPP_ENABLE_CLOG=yes` in the environment and unexpected
 *     options will be logged.
 *
 * @param options (optional) Configure the `UptimeCheckServiceConnection`
 * created by this function.
 */
std::shared_ptr<UptimeCheckServiceConnection> MakeUptimeCheckServiceConnection(
    Options options = {});

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace monitoring
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace monitoring_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<monitoring::UptimeCheckServiceConnection>
MakeUptimeCheckServiceConnection(std::shared_ptr<UptimeCheckServiceStub> stub,
                                 Options options);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace monitoring_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_MONITORING_UPTIME_CHECK_CONNECTION_H
