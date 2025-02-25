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
// source: google/cloud/aiplatform/v1/feature_online_store_admin_service.proto

#include "google/cloud/aiplatform/v1/internal/feature_online_store_admin_metadata_decorator.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include "google/cloud/internal/api_client_header.h"
#include "google/cloud/internal/url_encode.h"
#include "google/cloud/status_or.h"
#include <google/cloud/aiplatform/v1/feature_online_store_admin_service.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace aiplatform_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

FeatureOnlineStoreAdminServiceMetadata::FeatureOnlineStoreAdminServiceMetadata(
    std::shared_ptr<FeatureOnlineStoreAdminServiceStub> child,
    std::multimap<std::string, std::string> fixed_metadata,
    std::string api_client_header)
    : child_(std::move(child)),
      fixed_metadata_(std::move(fixed_metadata)),
      api_client_header_(
          api_client_header.empty()
              ? google::cloud::internal::GeneratedLibClientHeader()
              : std::move(api_client_header)) {}

future<StatusOr<google::longrunning::Operation>>
FeatureOnlineStoreAdminServiceMetadata::AsyncCreateFeatureOnlineStore(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::aiplatform::v1::CreateFeatureOnlineStoreRequest const&
        request) {
  SetMetadata(*context, *options,
              absl::StrCat("parent=", internal::UrlEncode(request.parent())));
  return child_->AsyncCreateFeatureOnlineStore(cq, std::move(context),
                                               std::move(options), request);
}

StatusOr<google::cloud::aiplatform::v1::FeatureOnlineStore>
FeatureOnlineStoreAdminServiceMetadata::GetFeatureOnlineStore(
    grpc::ClientContext& context, Options const& options,
    google::cloud::aiplatform::v1::GetFeatureOnlineStoreRequest const&
        request) {
  SetMetadata(context, options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->GetFeatureOnlineStore(context, options, request);
}

StatusOr<google::cloud::aiplatform::v1::ListFeatureOnlineStoresResponse>
FeatureOnlineStoreAdminServiceMetadata::ListFeatureOnlineStores(
    grpc::ClientContext& context, Options const& options,
    google::cloud::aiplatform::v1::ListFeatureOnlineStoresRequest const&
        request) {
  SetMetadata(context, options,
              absl::StrCat("parent=", internal::UrlEncode(request.parent())));
  return child_->ListFeatureOnlineStores(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
FeatureOnlineStoreAdminServiceMetadata::AsyncUpdateFeatureOnlineStore(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::aiplatform::v1::UpdateFeatureOnlineStoreRequest const&
        request) {
  SetMetadata(
      *context, *options,
      absl::StrCat("feature_online_store.name=",
                   internal::UrlEncode(request.feature_online_store().name())));
  return child_->AsyncUpdateFeatureOnlineStore(cq, std::move(context),
                                               std::move(options), request);
}

future<StatusOr<google::longrunning::Operation>>
FeatureOnlineStoreAdminServiceMetadata::AsyncDeleteFeatureOnlineStore(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::aiplatform::v1::DeleteFeatureOnlineStoreRequest const&
        request) {
  SetMetadata(*context, *options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->AsyncDeleteFeatureOnlineStore(cq, std::move(context),
                                               std::move(options), request);
}

future<StatusOr<google::longrunning::Operation>>
FeatureOnlineStoreAdminServiceMetadata::AsyncCreateFeatureView(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::aiplatform::v1::CreateFeatureViewRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("parent=", internal::UrlEncode(request.parent())));
  return child_->AsyncCreateFeatureView(cq, std::move(context),
                                        std::move(options), request);
}

StatusOr<google::cloud::aiplatform::v1::FeatureView>
FeatureOnlineStoreAdminServiceMetadata::GetFeatureView(
    grpc::ClientContext& context, Options const& options,
    google::cloud::aiplatform::v1::GetFeatureViewRequest const& request) {
  SetMetadata(context, options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->GetFeatureView(context, options, request);
}

StatusOr<google::cloud::aiplatform::v1::ListFeatureViewsResponse>
FeatureOnlineStoreAdminServiceMetadata::ListFeatureViews(
    grpc::ClientContext& context, Options const& options,
    google::cloud::aiplatform::v1::ListFeatureViewsRequest const& request) {
  SetMetadata(context, options,
              absl::StrCat("parent=", internal::UrlEncode(request.parent())));
  return child_->ListFeatureViews(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
FeatureOnlineStoreAdminServiceMetadata::AsyncUpdateFeatureView(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::aiplatform::v1::UpdateFeatureViewRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("feature_view.name=",
                           internal::UrlEncode(request.feature_view().name())));
  return child_->AsyncUpdateFeatureView(cq, std::move(context),
                                        std::move(options), request);
}

future<StatusOr<google::longrunning::Operation>>
FeatureOnlineStoreAdminServiceMetadata::AsyncDeleteFeatureView(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::aiplatform::v1::DeleteFeatureViewRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->AsyncDeleteFeatureView(cq, std::move(context),
                                        std::move(options), request);
}

StatusOr<google::cloud::aiplatform::v1::SyncFeatureViewResponse>
FeatureOnlineStoreAdminServiceMetadata::SyncFeatureView(
    grpc::ClientContext& context, Options const& options,
    google::cloud::aiplatform::v1::SyncFeatureViewRequest const& request) {
  SetMetadata(context, options,
              absl::StrCat("feature_view=",
                           internal::UrlEncode(request.feature_view())));
  return child_->SyncFeatureView(context, options, request);
}

StatusOr<google::cloud::aiplatform::v1::FeatureViewSync>
FeatureOnlineStoreAdminServiceMetadata::GetFeatureViewSync(
    grpc::ClientContext& context, Options const& options,
    google::cloud::aiplatform::v1::GetFeatureViewSyncRequest const& request) {
  SetMetadata(context, options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->GetFeatureViewSync(context, options, request);
}

StatusOr<google::cloud::aiplatform::v1::ListFeatureViewSyncsResponse>
FeatureOnlineStoreAdminServiceMetadata::ListFeatureViewSyncs(
    grpc::ClientContext& context, Options const& options,
    google::cloud::aiplatform::v1::ListFeatureViewSyncsRequest const& request) {
  SetMetadata(context, options,
              absl::StrCat("parent=", internal::UrlEncode(request.parent())));
  return child_->ListFeatureViewSyncs(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
FeatureOnlineStoreAdminServiceMetadata::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::GetOperationRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->AsyncGetOperation(cq, std::move(context), std::move(options),
                                   request);
}

future<Status> FeatureOnlineStoreAdminServiceMetadata::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::CancelOperationRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->AsyncCancelOperation(cq, std::move(context),
                                      std::move(options), request);
}

void FeatureOnlineStoreAdminServiceMetadata::SetMetadata(
    grpc::ClientContext& context, Options const& options,
    std::string const& request_params) {
  context.AddMetadata("x-goog-request-params", request_params);
  SetMetadata(context, options);
}

void FeatureOnlineStoreAdminServiceMetadata::SetMetadata(
    grpc::ClientContext& context, Options const& options) {
  google::cloud::internal::SetMetadata(context, options, fixed_metadata_,
                                       api_client_header_);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace aiplatform_v1_internal
}  // namespace cloud
}  // namespace google
