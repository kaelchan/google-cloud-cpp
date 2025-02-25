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

#include "google/cloud/aiplatform/v1/internal/notebook_auth_decorator.h"
#include <google/cloud/aiplatform/v1/notebook_service.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace aiplatform_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

NotebookServiceAuth::NotebookServiceAuth(
    std::shared_ptr<google::cloud::internal::GrpcAuthenticationStrategy> auth,
    std::shared_ptr<NotebookServiceStub> child)
    : auth_(std::move(auth)), child_(std::move(child)) {}

future<StatusOr<google::longrunning::Operation>>
NotebookServiceAuth::AsyncCreateNotebookRuntimeTemplate(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::aiplatform::v1::CreateNotebookRuntimeTemplateRequest const&
        request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncCreateNotebookRuntimeTemplate(
            cq, *std::move(context), std::move(options), request);
      });
}

StatusOr<google::cloud::aiplatform::v1::NotebookRuntimeTemplate>
NotebookServiceAuth::GetNotebookRuntimeTemplate(
    grpc::ClientContext& context, Options const& options,
    google::cloud::aiplatform::v1::GetNotebookRuntimeTemplateRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetNotebookRuntimeTemplate(context, options, request);
}

StatusOr<google::cloud::aiplatform::v1::ListNotebookRuntimeTemplatesResponse>
NotebookServiceAuth::ListNotebookRuntimeTemplates(
    grpc::ClientContext& context, Options const& options,
    google::cloud::aiplatform::v1::ListNotebookRuntimeTemplatesRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ListNotebookRuntimeTemplates(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
NotebookServiceAuth::AsyncDeleteNotebookRuntimeTemplate(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::aiplatform::v1::DeleteNotebookRuntimeTemplateRequest const&
        request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncDeleteNotebookRuntimeTemplate(
            cq, *std::move(context), std::move(options), request);
      });
}

future<StatusOr<google::longrunning::Operation>>
NotebookServiceAuth::AsyncAssignNotebookRuntime(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::aiplatform::v1::AssignNotebookRuntimeRequest const&
        request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncAssignNotebookRuntime(cq, *std::move(context),
                                                 std::move(options), request);
      });
}

StatusOr<google::cloud::aiplatform::v1::NotebookRuntime>
NotebookServiceAuth::GetNotebookRuntime(
    grpc::ClientContext& context, Options const& options,
    google::cloud::aiplatform::v1::GetNotebookRuntimeRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetNotebookRuntime(context, options, request);
}

StatusOr<google::cloud::aiplatform::v1::ListNotebookRuntimesResponse>
NotebookServiceAuth::ListNotebookRuntimes(
    grpc::ClientContext& context, Options const& options,
    google::cloud::aiplatform::v1::ListNotebookRuntimesRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ListNotebookRuntimes(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
NotebookServiceAuth::AsyncDeleteNotebookRuntime(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::aiplatform::v1::DeleteNotebookRuntimeRequest const&
        request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncDeleteNotebookRuntime(cq, *std::move(context),
                                                 std::move(options), request);
      });
}

future<StatusOr<google::longrunning::Operation>>
NotebookServiceAuth::AsyncUpgradeNotebookRuntime(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::aiplatform::v1::UpgradeNotebookRuntimeRequest const&
        request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncUpgradeNotebookRuntime(cq, *std::move(context),
                                                  std::move(options), request);
      });
}

future<StatusOr<google::longrunning::Operation>>
NotebookServiceAuth::AsyncStartNotebookRuntime(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::aiplatform::v1::StartNotebookRuntimeRequest const& request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncStartNotebookRuntime(cq, *std::move(context),
                                                std::move(options), request);
      });
}

future<StatusOr<google::longrunning::Operation>>
NotebookServiceAuth::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::GetOperationRequest const& request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncGetOperation(cq, *std::move(context),
                                        std::move(options), request);
      });
}

future<Status> NotebookServiceAuth::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::CancelOperationRequest const& request) {
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) return make_ready_future(std::move(context).status());
        return child->AsyncCancelOperation(cq, *std::move(context),
                                           std::move(options), request);
      });
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace aiplatform_v1_internal
}  // namespace cloud
}  // namespace google
