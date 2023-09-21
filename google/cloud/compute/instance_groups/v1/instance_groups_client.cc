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
// source: google/cloud/compute/instance_groups/v1/instance_groups.proto

#include "google/cloud/compute/instance_groups/v1/instance_groups_client.h"
#include <memory>

namespace google {
namespace cloud {
namespace compute_instance_groups_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

InstanceGroupsClient::InstanceGroupsClient(
    std::shared_ptr<InstanceGroupsConnection> connection, Options opts)
    : connection_(std::move(connection)),
      options_(
          internal::MergeOptions(std::move(opts), connection_->options())) {}
InstanceGroupsClient::~InstanceGroupsClient() = default;

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
InstanceGroupsClient::AddInstances(
    std::string const& project, std::string const& zone,
    std::string const& instance_group,
    google::cloud::cpp::compute::v1::InstanceGroupsAddInstancesRequest const&
        instance_groups_add_instances_request_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::instance_groups::v1::AddInstancesRequest request;
  request.set_project(project);
  request.set_zone(zone);
  request.set_instance_group(instance_group);
  *request.mutable_instance_groups_add_instances_request_resource() =
      instance_groups_add_instances_request_resource;
  return connection_->AddInstances(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
InstanceGroupsClient::AddInstances(
    google::cloud::cpp::compute::instance_groups::v1::AddInstancesRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->AddInstances(request);
}

StreamRange<std::pair<
    std::string, google::cloud::cpp::compute::v1::InstanceGroupsScopedList>>
InstanceGroupsClient::AggregatedListInstanceGroups(std::string const& project,
                                                   Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::instance_groups::v1::
      AggregatedListInstanceGroupsRequest request;
  request.set_project(project);
  return connection_->AggregatedListInstanceGroups(request);
}

StreamRange<std::pair<
    std::string, google::cloud::cpp::compute::v1::InstanceGroupsScopedList>>
InstanceGroupsClient::AggregatedListInstanceGroups(
    google::cloud::cpp::compute::instance_groups::v1::
        AggregatedListInstanceGroupsRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->AggregatedListInstanceGroups(std::move(request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
InstanceGroupsClient::DeleteInstanceGroup(std::string const& project,
                                          std::string const& zone,
                                          std::string const& instance_group,
                                          Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::instance_groups::v1::DeleteInstanceGroupRequest
      request;
  request.set_project(project);
  request.set_zone(zone);
  request.set_instance_group(instance_group);
  return connection_->DeleteInstanceGroup(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
InstanceGroupsClient::DeleteInstanceGroup(
    google::cloud::cpp::compute::instance_groups::v1::
        DeleteInstanceGroupRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteInstanceGroup(request);
}

StatusOr<google::cloud::cpp::compute::v1::InstanceGroup>
InstanceGroupsClient::GetInstanceGroup(std::string const& project,
                                       std::string const& zone,
                                       std::string const& instance_group,
                                       Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::instance_groups::v1::GetInstanceGroupRequest
      request;
  request.set_project(project);
  request.set_zone(zone);
  request.set_instance_group(instance_group);
  return connection_->GetInstanceGroup(request);
}

StatusOr<google::cloud::cpp::compute::v1::InstanceGroup>
InstanceGroupsClient::GetInstanceGroup(
    google::cloud::cpp::compute::instance_groups::v1::
        GetInstanceGroupRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetInstanceGroup(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
InstanceGroupsClient::InsertInstanceGroup(
    std::string const& project, std::string const& zone,
    google::cloud::cpp::compute::v1::InstanceGroup const&
        instance_group_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::instance_groups::v1::InsertInstanceGroupRequest
      request;
  request.set_project(project);
  request.set_zone(zone);
  *request.mutable_instance_group_resource() = instance_group_resource;
  return connection_->InsertInstanceGroup(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
InstanceGroupsClient::InsertInstanceGroup(
    google::cloud::cpp::compute::instance_groups::v1::
        InsertInstanceGroupRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->InsertInstanceGroup(request);
}

StreamRange<google::cloud::cpp::compute::v1::InstanceGroup>
InstanceGroupsClient::ListInstanceGroups(std::string const& project,
                                         std::string const& zone,
                                         Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::instance_groups::v1::ListInstanceGroupsRequest
      request;
  request.set_project(project);
  request.set_zone(zone);
  return connection_->ListInstanceGroups(request);
}

StreamRange<google::cloud::cpp::compute::v1::InstanceGroup>
InstanceGroupsClient::ListInstanceGroups(
    google::cloud::cpp::compute::instance_groups::v1::ListInstanceGroupsRequest
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListInstanceGroups(std::move(request));
}

StreamRange<google::cloud::cpp::compute::v1::InstanceWithNamedPorts>
InstanceGroupsClient::ListInstances(
    std::string const& project, std::string const& zone,
    std::string const& instance_group,
    google::cloud::cpp::compute::v1::InstanceGroupsListInstancesRequest const&
        instance_groups_list_instances_request_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::instance_groups::v1::ListInstancesRequest
      request;
  request.set_project(project);
  request.set_zone(zone);
  request.set_instance_group(instance_group);
  *request.mutable_instance_groups_list_instances_request_resource() =
      instance_groups_list_instances_request_resource;
  return connection_->ListInstances(request);
}

StreamRange<google::cloud::cpp::compute::v1::InstanceWithNamedPorts>
InstanceGroupsClient::ListInstances(
    google::cloud::cpp::compute::instance_groups::v1::ListInstancesRequest
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListInstances(std::move(request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
InstanceGroupsClient::RemoveInstances(
    std::string const& project, std::string const& zone,
    std::string const& instance_group,
    google::cloud::cpp::compute::v1::InstanceGroupsRemoveInstancesRequest const&
        instance_groups_remove_instances_request_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::instance_groups::v1::RemoveInstancesRequest
      request;
  request.set_project(project);
  request.set_zone(zone);
  request.set_instance_group(instance_group);
  *request.mutable_instance_groups_remove_instances_request_resource() =
      instance_groups_remove_instances_request_resource;
  return connection_->RemoveInstances(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
InstanceGroupsClient::RemoveInstances(
    google::cloud::cpp::compute::instance_groups::v1::
        RemoveInstancesRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->RemoveInstances(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
InstanceGroupsClient::SetNamedPorts(
    std::string const& project, std::string const& zone,
    std::string const& instance_group,
    google::cloud::cpp::compute::v1::InstanceGroupsSetNamedPortsRequest const&
        instance_groups_set_named_ports_request_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::instance_groups::v1::SetNamedPortsRequest
      request;
  request.set_project(project);
  request.set_zone(zone);
  request.set_instance_group(instance_group);
  *request.mutable_instance_groups_set_named_ports_request_resource() =
      instance_groups_set_named_ports_request_resource;
  return connection_->SetNamedPorts(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
InstanceGroupsClient::SetNamedPorts(
    google::cloud::cpp::compute::instance_groups::v1::
        SetNamedPortsRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->SetNamedPorts(request);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_instance_groups_v1
}  // namespace cloud
}  // namespace google
