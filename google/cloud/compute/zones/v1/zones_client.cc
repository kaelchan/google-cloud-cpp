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
// source: google/cloud/compute/zones/v1/zones.proto

#include "google/cloud/compute/zones/v1/zones_client.h"
#include <memory>

namespace google {
namespace cloud {
namespace compute_zones_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

ZonesClient::ZonesClient(std::shared_ptr<ZonesConnection> connection,
                         Options opts)
    : connection_(std::move(connection)),
      options_(
          internal::MergeOptions(std::move(opts), connection_->options())) {}
ZonesClient::~ZonesClient() = default;

StatusOr<google::cloud::cpp::compute::v1::Zone> ZonesClient::GetZone(
    std::string const& project, std::string const& zone, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::zones::v1::GetZoneRequest request;
  request.set_project(project);
  request.set_zone(zone);
  return connection_->GetZone(request);
}

StatusOr<google::cloud::cpp::compute::v1::Zone> ZonesClient::GetZone(
    google::cloud::cpp::compute::zones::v1::GetZoneRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetZone(request);
}

StreamRange<google::cloud::cpp::compute::v1::Zone> ZonesClient::ListZones(
    std::string const& project, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::zones::v1::ListZonesRequest request;
  request.set_project(project);
  return connection_->ListZones(request);
}

StreamRange<google::cloud::cpp::compute::v1::Zone> ZonesClient::ListZones(
    google::cloud::cpp::compute::zones::v1::ListZonesRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListZones(std::move(request));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_zones_v1
}  // namespace cloud
}  // namespace google
