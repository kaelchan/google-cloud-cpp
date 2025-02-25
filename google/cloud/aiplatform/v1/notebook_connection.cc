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
// source: google/cloud/aiplatform/v1/notebook_service.proto

#include "google/cloud/aiplatform/v1/notebook_connection.h"
#include "google/cloud/aiplatform/v1/internal/notebook_connection_impl.h"
#include "google/cloud/aiplatform/v1/internal/notebook_option_defaults.h"
#include "google/cloud/aiplatform/v1/internal/notebook_stub_factory.h"
#include "google/cloud/aiplatform/v1/internal/notebook_tracing_connection.h"
#include "google/cloud/aiplatform/v1/notebook_options.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/credentials.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/pagination_range.h"
#include "google/cloud/internal/unified_grpc_credentials.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace aiplatform_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

NotebookServiceConnection::~NotebookServiceConnection() = default;

future<StatusOr<google::cloud::aiplatform::v1::NotebookRuntimeTemplate>>
NotebookServiceConnection::CreateNotebookRuntimeTemplate(
    google::cloud::aiplatform::v1::
        CreateNotebookRuntimeTemplateRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::aiplatform::v1::NotebookRuntimeTemplate>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::cloud::aiplatform::v1::NotebookRuntimeTemplate>
NotebookServiceConnection::GetNotebookRuntimeTemplate(
    google::cloud::aiplatform::v1::GetNotebookRuntimeTemplateRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StreamRange<google::cloud::aiplatform::v1::NotebookRuntimeTemplate>
NotebookServiceConnection::ListNotebookRuntimeTemplates(
    google::cloud::aiplatform::v1::
        ListNotebookRuntimeTemplatesRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::aiplatform::v1::NotebookRuntimeTemplate>>();
}

future<StatusOr<google::cloud::aiplatform::v1::DeleteOperationMetadata>>
NotebookServiceConnection::DeleteNotebookRuntimeTemplate(
    google::cloud::aiplatform::v1::
        DeleteNotebookRuntimeTemplateRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::aiplatform::v1::DeleteOperationMetadata>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::aiplatform::v1::NotebookRuntime>>
NotebookServiceConnection::AssignNotebookRuntime(
    google::cloud::aiplatform::v1::AssignNotebookRuntimeRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::aiplatform::v1::NotebookRuntime>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::cloud::aiplatform::v1::NotebookRuntime>
NotebookServiceConnection::GetNotebookRuntime(
    google::cloud::aiplatform::v1::GetNotebookRuntimeRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StreamRange<google::cloud::aiplatform::v1::NotebookRuntime>
NotebookServiceConnection::ListNotebookRuntimes(
    google::cloud::aiplatform::v1::
        ListNotebookRuntimesRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::aiplatform::v1::NotebookRuntime>>();
}

future<StatusOr<google::cloud::aiplatform::v1::DeleteOperationMetadata>>
NotebookServiceConnection::DeleteNotebookRuntime(
    google::cloud::aiplatform::v1::DeleteNotebookRuntimeRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::aiplatform::v1::DeleteOperationMetadata>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::aiplatform::v1::UpgradeNotebookRuntimeResponse>>
NotebookServiceConnection::UpgradeNotebookRuntime(
    google::cloud::aiplatform::v1::UpgradeNotebookRuntimeRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::aiplatform::v1::UpgradeNotebookRuntimeResponse>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::aiplatform::v1::StartNotebookRuntimeResponse>>
NotebookServiceConnection::StartNotebookRuntime(
    google::cloud::aiplatform::v1::StartNotebookRuntimeRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::aiplatform::v1::StartNotebookRuntimeResponse>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

std::shared_ptr<NotebookServiceConnection> MakeNotebookServiceConnection(
    std::string const& location, Options options) {
  internal::CheckExpectedOptions<CommonOptionList, GrpcOptionList,
                                 UnifiedCredentialsOptionList,
                                 NotebookServicePolicyOptionList>(options,
                                                                  __func__);
  options = aiplatform_v1_internal::NotebookServiceDefaultOptions(
      location, std::move(options));
  auto background = internal::MakeBackgroundThreadsFactory(options)();
  auto auth = internal::CreateAuthenticationStrategy(background->cq(), options);
  auto stub = aiplatform_v1_internal::CreateDefaultNotebookServiceStub(
      std::move(auth), options);
  return aiplatform_v1_internal::MakeNotebookServiceTracingConnection(
      std::make_shared<aiplatform_v1_internal::NotebookServiceConnectionImpl>(
          std::move(background), std::move(stub), std::move(options)));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace aiplatform_v1
}  // namespace cloud
}  // namespace google
