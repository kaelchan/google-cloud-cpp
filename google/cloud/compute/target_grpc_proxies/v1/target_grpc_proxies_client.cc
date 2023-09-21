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
// source: google/cloud/compute/target_grpc_proxies/v1/target_grpc_proxies.proto

#include "google/cloud/compute/target_grpc_proxies/v1/target_grpc_proxies_client.h"
#include <memory>

namespace google {
namespace cloud {
namespace compute_target_grpc_proxies_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

TargetGrpcProxiesClient::TargetGrpcProxiesClient(
    std::shared_ptr<TargetGrpcProxiesConnection> connection, Options opts)
    : connection_(std::move(connection)),
      options_(
          internal::MergeOptions(std::move(opts), connection_->options())) {}
TargetGrpcProxiesClient::~TargetGrpcProxiesClient() = default;

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
TargetGrpcProxiesClient::DeleteTargetGrpcProxy(
    std::string const& project, std::string const& target_grpc_proxy,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::target_grpc_proxies::v1::
      DeleteTargetGrpcProxyRequest request;
  request.set_project(project);
  request.set_target_grpc_proxy(target_grpc_proxy);
  return connection_->DeleteTargetGrpcProxy(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
TargetGrpcProxiesClient::DeleteTargetGrpcProxy(
    google::cloud::cpp::compute::target_grpc_proxies::v1::
        DeleteTargetGrpcProxyRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteTargetGrpcProxy(request);
}

StatusOr<google::cloud::cpp::compute::v1::TargetGrpcProxy>
TargetGrpcProxiesClient::GetTargetGrpcProxy(
    std::string const& project, std::string const& target_grpc_proxy,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::target_grpc_proxies::v1::
      GetTargetGrpcProxyRequest request;
  request.set_project(project);
  request.set_target_grpc_proxy(target_grpc_proxy);
  return connection_->GetTargetGrpcProxy(request);
}

StatusOr<google::cloud::cpp::compute::v1::TargetGrpcProxy>
TargetGrpcProxiesClient::GetTargetGrpcProxy(
    google::cloud::cpp::compute::target_grpc_proxies::v1::
        GetTargetGrpcProxyRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetTargetGrpcProxy(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
TargetGrpcProxiesClient::InsertTargetGrpcProxy(
    std::string const& project,
    google::cloud::cpp::compute::v1::TargetGrpcProxy const&
        target_grpc_proxy_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::target_grpc_proxies::v1::
      InsertTargetGrpcProxyRequest request;
  request.set_project(project);
  *request.mutable_target_grpc_proxy_resource() = target_grpc_proxy_resource;
  return connection_->InsertTargetGrpcProxy(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
TargetGrpcProxiesClient::InsertTargetGrpcProxy(
    google::cloud::cpp::compute::target_grpc_proxies::v1::
        InsertTargetGrpcProxyRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->InsertTargetGrpcProxy(request);
}

StreamRange<google::cloud::cpp::compute::v1::TargetGrpcProxy>
TargetGrpcProxiesClient::ListTargetGrpcProxies(std::string const& project,
                                               Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::target_grpc_proxies::v1::
      ListTargetGrpcProxiesRequest request;
  request.set_project(project);
  return connection_->ListTargetGrpcProxies(request);
}

StreamRange<google::cloud::cpp::compute::v1::TargetGrpcProxy>
TargetGrpcProxiesClient::ListTargetGrpcProxies(
    google::cloud::cpp::compute::target_grpc_proxies::v1::
        ListTargetGrpcProxiesRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListTargetGrpcProxies(std::move(request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
TargetGrpcProxiesClient::PatchTargetGrpcProxy(
    std::string const& project, std::string const& target_grpc_proxy,
    google::cloud::cpp::compute::v1::TargetGrpcProxy const&
        target_grpc_proxy_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::target_grpc_proxies::v1::
      PatchTargetGrpcProxyRequest request;
  request.set_project(project);
  request.set_target_grpc_proxy(target_grpc_proxy);
  *request.mutable_target_grpc_proxy_resource() = target_grpc_proxy_resource;
  return connection_->PatchTargetGrpcProxy(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
TargetGrpcProxiesClient::PatchTargetGrpcProxy(
    google::cloud::cpp::compute::target_grpc_proxies::v1::
        PatchTargetGrpcProxyRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->PatchTargetGrpcProxy(request);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_target_grpc_proxies_v1
}  // namespace cloud
}  // namespace google
