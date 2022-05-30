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
// source: google/cloud/baremetalsolution/v2/baremetalsolution.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BAREMETALSOLUTION_BARE_METAL_SOLUTION_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BAREMETALSOLUTION_BARE_METAL_SOLUTION_CONNECTION_H

#include "google/cloud/baremetalsolution/bare_metal_solution_connection_idempotency_policy.h"
#include "google/cloud/baremetalsolution/internal/bare_metal_solution_retry_traits.h"
#include "google/cloud/baremetalsolution/internal/bare_metal_solution_stub.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/future.h"
#include "google/cloud/options.h"
#include "google/cloud/polling_policy.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace baremetalsolution {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using BareMetalSolutionRetryPolicy =
    ::google::cloud::internal::TraitBasedRetryPolicy<
        baremetalsolution_internal::BareMetalSolutionRetryTraits>;

using BareMetalSolutionLimitedTimeRetryPolicy =
    ::google::cloud::internal::LimitedTimeRetryPolicy<
        baremetalsolution_internal::BareMetalSolutionRetryTraits>;

using BareMetalSolutionLimitedErrorCountRetryPolicy =
    ::google::cloud::internal::LimitedErrorCountRetryPolicy<
        baremetalsolution_internal::BareMetalSolutionRetryTraits>;

/**
 * The `BareMetalSolutionConnection` object for `BareMetalSolutionClient`.
 *
 * This interface defines virtual methods for each of the user-facing overload
 * sets in `BareMetalSolutionClient`. This allows users to inject custom
 * behavior (e.g., with a Google Mock object) when writing tests that use
 * objects of type `BareMetalSolutionClient`.
 *
 * To create a concrete instance, see `MakeBareMetalSolutionConnection()`.
 *
 * For mocking, see `baremetalsolution_mocks::MockBareMetalSolutionConnection`.
 */
class BareMetalSolutionConnection {
 public:
  virtual ~BareMetalSolutionConnection() = 0;

  virtual Options options() { return Options{}; }

  virtual StreamRange<google::cloud::baremetalsolution::v2::Instance>
  ListInstances(
      google::cloud::baremetalsolution::v2::ListInstancesRequest request);

  virtual StatusOr<google::cloud::baremetalsolution::v2::Instance> GetInstance(
      google::cloud::baremetalsolution::v2::GetInstanceRequest const& request);

  virtual future<
      StatusOr<google::cloud::baremetalsolution::v2::ResetInstanceResponse>>
  ResetInstance(
      google::cloud::baremetalsolution::v2::ResetInstanceRequest const&
          request);

  virtual StreamRange<google::cloud::baremetalsolution::v2::Volume> ListVolumes(
      google::cloud::baremetalsolution::v2::ListVolumesRequest request);

  virtual StatusOr<google::cloud::baremetalsolution::v2::Volume> GetVolume(
      google::cloud::baremetalsolution::v2::GetVolumeRequest const& request);

  virtual future<StatusOr<google::cloud::baremetalsolution::v2::Volume>>
  UpdateVolume(
      google::cloud::baremetalsolution::v2::UpdateVolumeRequest const& request);

  virtual StreamRange<google::cloud::baremetalsolution::v2::Network>
  ListNetworks(
      google::cloud::baremetalsolution::v2::ListNetworksRequest request);

  virtual StatusOr<google::cloud::baremetalsolution::v2::Network> GetNetwork(
      google::cloud::baremetalsolution::v2::GetNetworkRequest const& request);

  virtual StreamRange<
      google::cloud::baremetalsolution::v2::SnapshotSchedulePolicy>
  ListSnapshotSchedulePolicies(
      google::cloud::baremetalsolution::v2::ListSnapshotSchedulePoliciesRequest
          request);

  virtual StatusOr<google::cloud::baremetalsolution::v2::SnapshotSchedulePolicy>
  GetSnapshotSchedulePolicy(
      google::cloud::baremetalsolution::v2::
          GetSnapshotSchedulePolicyRequest const& request);

  virtual StatusOr<google::cloud::baremetalsolution::v2::SnapshotSchedulePolicy>
  CreateSnapshotSchedulePolicy(
      google::cloud::baremetalsolution::v2::
          CreateSnapshotSchedulePolicyRequest const& request);

  virtual StatusOr<google::cloud::baremetalsolution::v2::SnapshotSchedulePolicy>
  UpdateSnapshotSchedulePolicy(
      google::cloud::baremetalsolution::v2::
          UpdateSnapshotSchedulePolicyRequest const& request);

  virtual Status DeleteSnapshotSchedulePolicy(
      google::cloud::baremetalsolution::v2::
          DeleteSnapshotSchedulePolicyRequest const& request);

  virtual StatusOr<google::cloud::baremetalsolution::v2::VolumeSnapshot>
  CreateVolumeSnapshot(
      google::cloud::baremetalsolution::v2::CreateVolumeSnapshotRequest const&
          request);

  virtual future<StatusOr<google::cloud::baremetalsolution::v2::VolumeSnapshot>>
  RestoreVolumeSnapshot(
      google::cloud::baremetalsolution::v2::RestoreVolumeSnapshotRequest const&
          request);

  virtual Status DeleteVolumeSnapshot(
      google::cloud::baremetalsolution::v2::DeleteVolumeSnapshotRequest const&
          request);

  virtual StatusOr<google::cloud::baremetalsolution::v2::VolumeSnapshot>
  GetVolumeSnapshot(
      google::cloud::baremetalsolution::v2::GetVolumeSnapshotRequest const&
          request);

  virtual StreamRange<google::cloud::baremetalsolution::v2::VolumeSnapshot>
  ListVolumeSnapshots(
      google::cloud::baremetalsolution::v2::ListVolumeSnapshotsRequest request);

  virtual StatusOr<google::cloud::baremetalsolution::v2::Lun> GetLun(
      google::cloud::baremetalsolution::v2::GetLunRequest const& request);

  virtual StreamRange<google::cloud::baremetalsolution::v2::Lun> ListLuns(
      google::cloud::baremetalsolution::v2::ListLunsRequest request);
};

/**
 * A factory function to construct an object of type
 * `BareMetalSolutionConnection`.
 *
 * The returned connection object should not be used directly; instead it
 * should be passed as an argument to the constructor of
 * BareMetalSolutionClient, and that class used instead.
 *
 * The optional @p opts argument may be used to configure aspects of the
 * returned `BareMetalSolutionConnection`. Expected options are any of the types
 * in the following option lists:
 *
 * - `google::cloud::CommonOptionList`
 * - `google::cloud::GrpcOptionList`
 * - `google::cloud::baremetalsolution::BareMetalSolutionPolicyOptionList`
 *
 * @note Unrecognized options will be ignored. To debug issues with options set
 *     `GOOGLE_CLOUD_CPP_ENABLE_CLOG=yes` in the environment and unexpected
 *     options will be logged.
 *
 * @param options (optional) Configure the `BareMetalSolutionConnection` created
 * by this function.
 */
std::shared_ptr<BareMetalSolutionConnection> MakeBareMetalSolutionConnection(
    Options options = {});

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace baremetalsolution
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace baremetalsolution_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<baremetalsolution::BareMetalSolutionConnection>
MakeBareMetalSolutionConnection(std::shared_ptr<BareMetalSolutionStub> stub,
                                Options options);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace baremetalsolution_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BAREMETALSOLUTION_BARE_METAL_SOLUTION_CONNECTION_H
