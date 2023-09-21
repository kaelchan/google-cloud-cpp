// Copyright 2023 Google LLC
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
// source: google/cloud/compute/snapshots/v1/snapshots.proto

#include "google/cloud/compute/snapshots/v1/snapshots_client.h"
#include <memory>

namespace google {
namespace cloud {
namespace compute_snapshots_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

SnapshotsClient::SnapshotsClient(
    std::shared_ptr<SnapshotsConnection> connection, Options opts)
    : connection_(std::move(connection)),
      options_(
          internal::MergeOptions(std::move(opts), connection_->options())) {}
SnapshotsClient::~SnapshotsClient() = default;

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
SnapshotsClient::DeleteSnapshot(std::string const& project,
                                std::string const& snapshot, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::snapshots::v1::DeleteSnapshotRequest request;
  request.set_project(project);
  request.set_snapshot(snapshot);
  return connection_->DeleteSnapshot(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
SnapshotsClient::DeleteSnapshot(
    google::cloud::cpp::compute::snapshots::v1::DeleteSnapshotRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteSnapshot(request);
}

StatusOr<google::cloud::cpp::compute::v1::Snapshot>
SnapshotsClient::GetSnapshot(std::string const& project,
                             std::string const& snapshot, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::snapshots::v1::GetSnapshotRequest request;
  request.set_project(project);
  request.set_snapshot(snapshot);
  return connection_->GetSnapshot(request);
}

StatusOr<google::cloud::cpp::compute::v1::Snapshot>
SnapshotsClient::GetSnapshot(
    google::cloud::cpp::compute::snapshots::v1::GetSnapshotRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetSnapshot(request);
}

StatusOr<google::cloud::cpp::compute::v1::Policy> SnapshotsClient::GetIamPolicy(
    std::string const& project, std::string const& resource, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::snapshots::v1::GetIamPolicyRequest request;
  request.set_project(project);
  request.set_resource(resource);
  return connection_->GetIamPolicy(request);
}

StatusOr<google::cloud::cpp::compute::v1::Policy> SnapshotsClient::GetIamPolicy(
    google::cloud::cpp::compute::snapshots::v1::GetIamPolicyRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetIamPolicy(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
SnapshotsClient::InsertSnapshot(
    std::string const& project,
    google::cloud::cpp::compute::v1::Snapshot const& snapshot_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::snapshots::v1::InsertSnapshotRequest request;
  request.set_project(project);
  *request.mutable_snapshot_resource() = snapshot_resource;
  return connection_->InsertSnapshot(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
SnapshotsClient::InsertSnapshot(
    google::cloud::cpp::compute::snapshots::v1::InsertSnapshotRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->InsertSnapshot(request);
}

StreamRange<google::cloud::cpp::compute::v1::Snapshot>
SnapshotsClient::ListSnapshots(std::string const& project, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::snapshots::v1::ListSnapshotsRequest request;
  request.set_project(project);
  return connection_->ListSnapshots(request);
}

StreamRange<google::cloud::cpp::compute::v1::Snapshot>
SnapshotsClient::ListSnapshots(
    google::cloud::cpp::compute::snapshots::v1::ListSnapshotsRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListSnapshots(std::move(request));
}

StatusOr<google::cloud::cpp::compute::v1::Policy> SnapshotsClient::SetIamPolicy(
    std::string const& project, std::string const& resource,
    google::cloud::cpp::compute::v1::GlobalSetPolicyRequest const&
        global_set_policy_request_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::snapshots::v1::SetIamPolicyRequest request;
  request.set_project(project);
  request.set_resource(resource);
  *request.mutable_global_set_policy_request_resource() =
      global_set_policy_request_resource;
  return connection_->SetIamPolicy(request);
}

StatusOr<google::cloud::cpp::compute::v1::Policy> SnapshotsClient::SetIamPolicy(
    google::cloud::cpp::compute::snapshots::v1::SetIamPolicyRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->SetIamPolicy(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
SnapshotsClient::SetLabels(
    std::string const& project, std::string const& resource,
    google::cloud::cpp::compute::v1::GlobalSetLabelsRequest const&
        global_set_labels_request_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::snapshots::v1::SetLabelsRequest request;
  request.set_project(project);
  request.set_resource(resource);
  *request.mutable_global_set_labels_request_resource() =
      global_set_labels_request_resource;
  return connection_->SetLabels(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
SnapshotsClient::SetLabels(
    google::cloud::cpp::compute::snapshots::v1::SetLabelsRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->SetLabels(request);
}

StatusOr<google::cloud::cpp::compute::v1::TestPermissionsResponse>
SnapshotsClient::TestIamPermissions(
    std::string const& project, std::string const& resource,
    google::cloud::cpp::compute::v1::TestPermissionsRequest const&
        test_permissions_request_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::snapshots::v1::TestIamPermissionsRequest request;
  request.set_project(project);
  request.set_resource(resource);
  *request.mutable_test_permissions_request_resource() =
      test_permissions_request_resource;
  return connection_->TestIamPermissions(request);
}

StatusOr<google::cloud::cpp::compute::v1::TestPermissionsResponse>
SnapshotsClient::TestIamPermissions(
    google::cloud::cpp::compute::snapshots::v1::TestIamPermissionsRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->TestIamPermissions(request);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_snapshots_v1
}  // namespace cloud
}  // namespace google
