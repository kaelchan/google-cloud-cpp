// Copyright 2024 Google LLC
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
// source: generator/integration_tests/test_request_id.proto

#include "generator/integration_tests/golden/v1/internal/request_id_metadata_decorator.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include "google/cloud/internal/absl_str_join_quiet.h"
#include "google/cloud/internal/api_client_header.h"
#include "google/cloud/internal/routing_matcher.h"
#include "google/cloud/internal/url_encode.h"
#include "google/cloud/status_or.h"
#include <generator/integration_tests/test_request_id.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace golden_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

RequestIdServiceMetadata::RequestIdServiceMetadata(
    std::shared_ptr<RequestIdServiceStub> child,
    std::multimap<std::string, std::string> fixed_metadata,
    std::string api_client_header)
    : child_(std::move(child)),
      fixed_metadata_(std::move(fixed_metadata)),
      api_client_header_(
          api_client_header.empty()
              ? google::cloud::internal::GeneratedLibClientHeader()
              : std::move(api_client_header)) {}

StatusOr<google::test::requestid::v1::Foo>
RequestIdServiceMetadata::CreateFoo(
    grpc::ClientContext& context,
    Options const& options,
    google::test::requestid::v1::CreateFooRequest const& request) {
  std::vector<std::string> params;
  params.reserve(1);

  if (!request.parent().empty()) {
    params.push_back(absl::StrCat("parent=", internal::UrlEncode(request.parent())));
  }

  if (params.empty()) {
    SetMetadata(context, options);
  } else {
    SetMetadata(context, options, absl::StrJoin(params, "&"));
  }
  return child_->CreateFoo(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
RequestIdServiceMetadata::AsyncRenameFoo(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::test::requestid::v1::RenameFooRequest const& request) {
  std::vector<std::string> params;
  params.reserve(1);

  static auto* parent_matcher = []{
    return new google::cloud::internal::RoutingMatcher<google::test::requestid::v1::RenameFooRequest>{
      "parent=", {
      {[](google::test::requestid::v1::RenameFooRequest const& request) -> std::string const& {
        return request.name();
      },
      std::regex{"(projects/[^/]+/parents/[^/]+)/.*", std::regex::optimize}},
      }};
  }();
  parent_matcher->AppendParam(request, params);

  if (params.empty()) {
    SetMetadata(*context, *options);
  } else {
    SetMetadata(*context, *options, absl::StrJoin(params, "&"));
  }
  return child_->AsyncRenameFoo(
      cq, std::move(context), std::move(options), request);
}

StatusOr<google::test::requestid::v1::ListFoosResponse>
RequestIdServiceMetadata::ListFoos(
    grpc::ClientContext& context,
    Options const& options,
    google::test::requestid::v1::ListFoosRequest const& request) {
  std::vector<std::string> params;
  params.reserve(1);

  if (!request.parent().empty()) {
    params.push_back(absl::StrCat("parent=", internal::UrlEncode(request.parent())));
  }

  if (params.empty()) {
    SetMetadata(context, options);
  } else {
    SetMetadata(context, options, absl::StrJoin(params, "&"));
  }
  return child_->ListFoos(context, options, request);
}

future<StatusOr<google::test::requestid::v1::Foo>>
RequestIdServiceMetadata::AsyncCreateFoo(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::test::requestid::v1::CreateFooRequest const& request) {
  std::vector<std::string> params;
  params.reserve(1);

  if (!request.parent().empty()) {
    params.push_back(absl::StrCat("parent=", internal::UrlEncode(request.parent())));
  }

  if (params.empty()) {
    SetMetadata(*context, *options);
  } else {
    SetMetadata(*context, *options, absl::StrJoin(params, "&"));
  }
  return child_->AsyncCreateFoo(
      cq, std::move(context), std::move(options), request);
}

future<StatusOr<google::longrunning::Operation>>
RequestIdServiceMetadata::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::GetOperationRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->AsyncGetOperation(
      cq, std::move(context), std::move(options), request);
}

future<Status> RequestIdServiceMetadata::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::CancelOperationRequest const& request) {
  SetMetadata(*context, *options,
              absl::StrCat("name=", internal::UrlEncode(request.name())));
  return child_->AsyncCancelOperation(
      cq, std::move(context), std::move(options), request);
}

void RequestIdServiceMetadata::SetMetadata(grpc::ClientContext& context,
                                        Options const& options,
                                        std::string const& request_params) {
  context.AddMetadata("x-goog-request-params", request_params);
  SetMetadata(context, options);
}

void RequestIdServiceMetadata::SetMetadata(grpc::ClientContext& context,
                                        Options const& options) {
  google::cloud::internal::SetMetadata(
      context, options, fixed_metadata_, api_client_header_);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace golden_v1_internal
}  // namespace cloud
}  // namespace google
