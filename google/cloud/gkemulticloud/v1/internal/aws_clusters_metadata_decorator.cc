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
// source: google/cloud/gkemulticloud/v1/aws_service.proto

#include "google/cloud/gkemulticloud/v1/internal/aws_clusters_metadata_decorator.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include "google/cloud/internal/api_client_header.h"
#include "google/cloud/internal/url_encode.h"
#include "google/cloud/status_or.h"
#include <google/cloud/gkemulticloud/v1/aws_service.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace gkemulticloud_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

AwsClustersMetadata::AwsClustersMetadata(
    std::shared_ptr<AwsClustersStub> child,
    std::multimap<std::string, std::string> fixed_metadata,
    std::string api_client_header)
    : child_(std::move(child)),
      fixed_metadata_(std::move(fixed_metadata)),
      api_client_header_(
          api_client_header.empty()
              ? google::cloud::internal::GeneratedLibClientHeader()
              : std::move(api_client_header)) {}

future<StatusOr<google::longrunning::Operation>>
AwsClustersMetadata::AsyncCreateAwsCluster(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::gkemulticloud::v1::CreateAwsClusterRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("parent=", internal::UrlEncode(request.parent())));
  return child_->AsyncCreateAwsCluster(cq, std::move(context),
                                       std::move(options), request);
}

future<StatusOr<google::longrunning::Operation>>
AwsClustersMetadata::AsyncUpdateAwsCluster(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::gkemulticloud::v1::UpdateAwsClusterRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("aws_cluster.name=",
                           internal::UrlEncode(request.aws_cluster().name())));
  return child_->AsyncUpdateAwsCluster(cq, std::move(context),
                                       std::move(options), request);
}

StatusOr<google::cloud::gkemulticloud::v1::AwsCluster>
AwsClustersMetadata::GetAwsCluster(
    grpc::ClientContext& context, Options const& options,
    google::cloud::gkemulticloud::v1::GetAwsClusterRequest const& request) {
  SetMetadata(context, options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->GetAwsCluster(context, options, request);
}

StatusOr<google::cloud::gkemulticloud::v1::ListAwsClustersResponse>
AwsClustersMetadata::ListAwsClusters(
    grpc::ClientContext& context, Options const& options,
    google::cloud::gkemulticloud::v1::ListAwsClustersRequest const& request) {
  SetMetadata(context, options,
              absl::StrCat("parent=", internal::UrlEncode(request.parent())));
  return child_->ListAwsClusters(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
AwsClustersMetadata::AsyncDeleteAwsCluster(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::gkemulticloud::v1::DeleteAwsClusterRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->AsyncDeleteAwsCluster(cq, std::move(context),
                                       std::move(options), request);
}

StatusOr<google::cloud::gkemulticloud::v1::GenerateAwsClusterAgentTokenResponse>
AwsClustersMetadata::GenerateAwsClusterAgentToken(
    grpc::ClientContext& context, Options const& options,
    google::cloud::gkemulticloud::v1::GenerateAwsClusterAgentTokenRequest const&
        request) {
  SetMetadata(
      context, options,
      absl::StrCat("aws_cluster=", internal::UrlEncode(request.aws_cluster())));
  return child_->GenerateAwsClusterAgentToken(context, options, request);
}

StatusOr<google::cloud::gkemulticloud::v1::GenerateAwsAccessTokenResponse>
AwsClustersMetadata::GenerateAwsAccessToken(
    grpc::ClientContext& context, Options const& options,
    google::cloud::gkemulticloud::v1::GenerateAwsAccessTokenRequest const&
        request) {
  SetMetadata(
      context, options,
      absl::StrCat("aws_cluster=", internal::UrlEncode(request.aws_cluster())));
  return child_->GenerateAwsAccessToken(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
AwsClustersMetadata::AsyncCreateAwsNodePool(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::gkemulticloud::v1::CreateAwsNodePoolRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("parent=", internal::UrlEncode(request.parent())));
  return child_->AsyncCreateAwsNodePool(cq, std::move(context),
                                        std::move(options), request);
}

future<StatusOr<google::longrunning::Operation>>
AwsClustersMetadata::AsyncUpdateAwsNodePool(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::gkemulticloud::v1::UpdateAwsNodePoolRequest const& request) {
  SetMetadata(
      *context, *options,
      absl::StrCat("aws_node_pool.name=",
                   internal::UrlEncode(request.aws_node_pool().name())));
  return child_->AsyncUpdateAwsNodePool(cq, std::move(context),
                                        std::move(options), request);
}

future<StatusOr<google::longrunning::Operation>>
AwsClustersMetadata::AsyncRollbackAwsNodePoolUpdate(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::gkemulticloud::v1::RollbackAwsNodePoolUpdateRequest const&
        request) {
  SetMetadata(*context, *options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->AsyncRollbackAwsNodePoolUpdate(cq, std::move(context),
                                                std::move(options), request);
}

StatusOr<google::cloud::gkemulticloud::v1::AwsNodePool>
AwsClustersMetadata::GetAwsNodePool(
    grpc::ClientContext& context, Options const& options,
    google::cloud::gkemulticloud::v1::GetAwsNodePoolRequest const& request) {
  SetMetadata(context, options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->GetAwsNodePool(context, options, request);
}

StatusOr<google::cloud::gkemulticloud::v1::ListAwsNodePoolsResponse>
AwsClustersMetadata::ListAwsNodePools(
    grpc::ClientContext& context, Options const& options,
    google::cloud::gkemulticloud::v1::ListAwsNodePoolsRequest const& request) {
  SetMetadata(context, options,
              absl::StrCat("parent=", internal::UrlEncode(request.parent())));
  return child_->ListAwsNodePools(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
AwsClustersMetadata::AsyncDeleteAwsNodePool(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::gkemulticloud::v1::DeleteAwsNodePoolRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->AsyncDeleteAwsNodePool(cq, std::move(context),
                                        std::move(options), request);
}

StatusOr<google::cloud::gkemulticloud::v1::AwsOpenIdConfig>
AwsClustersMetadata::GetAwsOpenIdConfig(
    grpc::ClientContext& context, Options const& options,
    google::cloud::gkemulticloud::v1::GetAwsOpenIdConfigRequest const&
        request) {
  SetMetadata(
      context, options,
      absl::StrCat("aws_cluster=", internal::UrlEncode(request.aws_cluster())));
  return child_->GetAwsOpenIdConfig(context, options, request);
}

StatusOr<google::cloud::gkemulticloud::v1::AwsJsonWebKeys>
AwsClustersMetadata::GetAwsJsonWebKeys(
    grpc::ClientContext& context, Options const& options,
    google::cloud::gkemulticloud::v1::GetAwsJsonWebKeysRequest const& request) {
  SetMetadata(
      context, options,
      absl::StrCat("aws_cluster=", internal::UrlEncode(request.aws_cluster())));
  return child_->GetAwsJsonWebKeys(context, options, request);
}

StatusOr<google::cloud::gkemulticloud::v1::AwsServerConfig>
AwsClustersMetadata::GetAwsServerConfig(
    grpc::ClientContext& context, Options const& options,
    google::cloud::gkemulticloud::v1::GetAwsServerConfigRequest const&
        request) {
  SetMetadata(context, options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->GetAwsServerConfig(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
AwsClustersMetadata::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::GetOperationRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->AsyncGetOperation(cq, std::move(context), std::move(options),
                                   request);
}

future<Status> AwsClustersMetadata::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::CancelOperationRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->AsyncCancelOperation(cq, std::move(context),
                                      std::move(options), request);
}

void AwsClustersMetadata::SetMetadata(grpc::ClientContext& context,
                                      Options const& options,
                                      std::string const& request_params) {
  context.AddMetadata("x-goog-request-params", request_params);
  SetMetadata(context, options);
}

void AwsClustersMetadata::SetMetadata(grpc::ClientContext& context,
                                      Options const& options) {
  google::cloud::internal::SetMetadata(context, options, fixed_metadata_,
                                       api_client_header_);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace gkemulticloud_v1_internal
}  // namespace cloud
}  // namespace google
