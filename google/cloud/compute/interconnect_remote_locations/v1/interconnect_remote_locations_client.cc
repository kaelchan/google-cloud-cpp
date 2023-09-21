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
// source:
// google/cloud/compute/interconnect_remote_locations/v1/interconnect_remote_locations.proto

#include "google/cloud/compute/interconnect_remote_locations/v1/interconnect_remote_locations_client.h"
#include <memory>

namespace google {
namespace cloud {
namespace compute_interconnect_remote_locations_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

InterconnectRemoteLocationsClient::InterconnectRemoteLocationsClient(
    std::shared_ptr<InterconnectRemoteLocationsConnection> connection,
    Options opts)
    : connection_(std::move(connection)),
      options_(
          internal::MergeOptions(std::move(opts), connection_->options())) {}
InterconnectRemoteLocationsClient::~InterconnectRemoteLocationsClient() =
    default;

StatusOr<google::cloud::cpp::compute::v1::InterconnectRemoteLocation>
InterconnectRemoteLocationsClient::GetInterconnectRemoteLocation(
    std::string const& project, std::string const& interconnect_remote_location,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::interconnect_remote_locations::v1::
      GetInterconnectRemoteLocationRequest request;
  request.set_project(project);
  request.set_interconnect_remote_location(interconnect_remote_location);
  return connection_->GetInterconnectRemoteLocation(request);
}

StatusOr<google::cloud::cpp::compute::v1::InterconnectRemoteLocation>
InterconnectRemoteLocationsClient::GetInterconnectRemoteLocation(
    google::cloud::cpp::compute::interconnect_remote_locations::v1::
        GetInterconnectRemoteLocationRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetInterconnectRemoteLocation(request);
}

StreamRange<google::cloud::cpp::compute::v1::InterconnectRemoteLocation>
InterconnectRemoteLocationsClient::ListInterconnectRemoteLocations(
    std::string const& project, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::interconnect_remote_locations::v1::
      ListInterconnectRemoteLocationsRequest request;
  request.set_project(project);
  return connection_->ListInterconnectRemoteLocations(request);
}

StreamRange<google::cloud::cpp::compute::v1::InterconnectRemoteLocation>
InterconnectRemoteLocationsClient::ListInterconnectRemoteLocations(
    google::cloud::cpp::compute::interconnect_remote_locations::v1::
        ListInterconnectRemoteLocationsRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListInterconnectRemoteLocations(std::move(request));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_interconnect_remote_locations_v1
}  // namespace cloud
}  // namespace google
