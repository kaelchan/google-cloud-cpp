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
// source: google/cloud/compute/target_vpn_gateways/v1/target_vpn_gateways.proto

#include "google/cloud/compute/target_vpn_gateways/v1/target_vpn_gateways_client.h"
#include <memory>

namespace google {
namespace cloud {
namespace compute_target_vpn_gateways_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

TargetVpnGatewaysClient::TargetVpnGatewaysClient(
    std::shared_ptr<TargetVpnGatewaysConnection> connection, Options opts)
    : connection_(std::move(connection)),
      options_(
          internal::MergeOptions(std::move(opts), connection_->options())) {}
TargetVpnGatewaysClient::~TargetVpnGatewaysClient() = default;

StreamRange<std::pair<
    std::string, google::cloud::cpp::compute::v1::TargetVpnGatewaysScopedList>>
TargetVpnGatewaysClient::AggregatedListTargetVpnGateways(
    std::string const& project, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::target_vpn_gateways::v1::
      AggregatedListTargetVpnGatewaysRequest request;
  request.set_project(project);
  return connection_->AggregatedListTargetVpnGateways(request);
}

StreamRange<std::pair<
    std::string, google::cloud::cpp::compute::v1::TargetVpnGatewaysScopedList>>
TargetVpnGatewaysClient::AggregatedListTargetVpnGateways(
    google::cloud::cpp::compute::target_vpn_gateways::v1::
        AggregatedListTargetVpnGatewaysRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->AggregatedListTargetVpnGateways(std::move(request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
TargetVpnGatewaysClient::DeleteTargetVpnGateway(
    std::string const& project, std::string const& region,
    std::string const& target_vpn_gateway, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::target_vpn_gateways::v1::
      DeleteTargetVpnGatewayRequest request;
  request.set_project(project);
  request.set_region(region);
  request.set_target_vpn_gateway(target_vpn_gateway);
  return connection_->DeleteTargetVpnGateway(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
TargetVpnGatewaysClient::DeleteTargetVpnGateway(
    google::cloud::cpp::compute::target_vpn_gateways::v1::
        DeleteTargetVpnGatewayRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteTargetVpnGateway(request);
}

StatusOr<google::cloud::cpp::compute::v1::TargetVpnGateway>
TargetVpnGatewaysClient::GetTargetVpnGateway(
    std::string const& project, std::string const& region,
    std::string const& target_vpn_gateway, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::target_vpn_gateways::v1::
      GetTargetVpnGatewayRequest request;
  request.set_project(project);
  request.set_region(region);
  request.set_target_vpn_gateway(target_vpn_gateway);
  return connection_->GetTargetVpnGateway(request);
}

StatusOr<google::cloud::cpp::compute::v1::TargetVpnGateway>
TargetVpnGatewaysClient::GetTargetVpnGateway(
    google::cloud::cpp::compute::target_vpn_gateways::v1::
        GetTargetVpnGatewayRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetTargetVpnGateway(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
TargetVpnGatewaysClient::InsertTargetVpnGateway(
    std::string const& project, std::string const& region,
    google::cloud::cpp::compute::v1::TargetVpnGateway const&
        target_vpn_gateway_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::target_vpn_gateways::v1::
      InsertTargetVpnGatewayRequest request;
  request.set_project(project);
  request.set_region(region);
  *request.mutable_target_vpn_gateway_resource() = target_vpn_gateway_resource;
  return connection_->InsertTargetVpnGateway(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
TargetVpnGatewaysClient::InsertTargetVpnGateway(
    google::cloud::cpp::compute::target_vpn_gateways::v1::
        InsertTargetVpnGatewayRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->InsertTargetVpnGateway(request);
}

StreamRange<google::cloud::cpp::compute::v1::TargetVpnGateway>
TargetVpnGatewaysClient::ListTargetVpnGateways(std::string const& project,
                                               std::string const& region,
                                               Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::target_vpn_gateways::v1::
      ListTargetVpnGatewaysRequest request;
  request.set_project(project);
  request.set_region(region);
  return connection_->ListTargetVpnGateways(request);
}

StreamRange<google::cloud::cpp::compute::v1::TargetVpnGateway>
TargetVpnGatewaysClient::ListTargetVpnGateways(
    google::cloud::cpp::compute::target_vpn_gateways::v1::
        ListTargetVpnGatewaysRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListTargetVpnGateways(std::move(request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
TargetVpnGatewaysClient::SetLabels(
    std::string const& project, std::string const& region,
    std::string const& resource,
    google::cloud::cpp::compute::v1::RegionSetLabelsRequest const&
        region_set_labels_request_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::target_vpn_gateways::v1::SetLabelsRequest
      request;
  request.set_project(project);
  request.set_region(region);
  request.set_resource(resource);
  *request.mutable_region_set_labels_request_resource() =
      region_set_labels_request_resource;
  return connection_->SetLabels(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
TargetVpnGatewaysClient::SetLabels(
    google::cloud::cpp::compute::target_vpn_gateways::v1::
        SetLabelsRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->SetLabels(request);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_target_vpn_gateways_v1
}  // namespace cloud
}  // namespace google
