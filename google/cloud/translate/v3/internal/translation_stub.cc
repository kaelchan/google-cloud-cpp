// Copyright 2022 Google LLC
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
// source: google/cloud/translate/v3/translation_service.proto

#include "google/cloud/translate/v3/internal/translation_stub.h"
#include "google/cloud/grpc_error_delegate.h"
#include "google/cloud/status_or.h"
#include <google/cloud/translate/v3/translation_service.grpc.pb.h>
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace translate_v3_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

TranslationServiceStub::~TranslationServiceStub() = default;

StatusOr<google::cloud::translation::v3::TranslateTextResponse>
DefaultTranslationServiceStub::TranslateText(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::TranslateTextRequest const& request) {
  google::cloud::translation::v3::TranslateTextResponse response;
  auto status = grpc_stub_->TranslateText(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::translation::v3::DetectLanguageResponse>
DefaultTranslationServiceStub::DetectLanguage(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::DetectLanguageRequest const& request) {
  google::cloud::translation::v3::DetectLanguageResponse response;
  auto status = grpc_stub_->DetectLanguage(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::translation::v3::SupportedLanguages>
DefaultTranslationServiceStub::GetSupportedLanguages(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::GetSupportedLanguagesRequest const&
        request) {
  google::cloud::translation::v3::SupportedLanguages response;
  auto status = grpc_stub_->GetSupportedLanguages(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::translation::v3::TranslateDocumentResponse>
DefaultTranslationServiceStub::TranslateDocument(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::TranslateDocumentRequest const& request) {
  google::cloud::translation::v3::TranslateDocumentResponse response;
  auto status = grpc_stub_->TranslateDocument(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

future<StatusOr<google::longrunning::Operation>>
DefaultTranslationServiceStub::AsyncBatchTranslateText(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions,
    google::cloud::translation::v3::BatchTranslateTextRequest const& request) {
  return internal::MakeUnaryRpcImpl<
      google::cloud::translation::v3::BatchTranslateTextRequest,
      google::longrunning::Operation>(
      cq,
      [this](grpc::ClientContext* context,
             google::cloud::translation::v3::BatchTranslateTextRequest const&
                 request,
             grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncBatchTranslateText(context, request, cq);
      },
      request, std::move(context));
}

future<StatusOr<google::longrunning::Operation>>
DefaultTranslationServiceStub::AsyncBatchTranslateDocument(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions,
    google::cloud::translation::v3::BatchTranslateDocumentRequest const&
        request) {
  return internal::MakeUnaryRpcImpl<
      google::cloud::translation::v3::BatchTranslateDocumentRequest,
      google::longrunning::Operation>(
      cq,
      [this](
          grpc::ClientContext* context,
          google::cloud::translation::v3::BatchTranslateDocumentRequest const&
              request,
          grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncBatchTranslateDocument(context, request, cq);
      },
      request, std::move(context));
}

future<StatusOr<google::longrunning::Operation>>
DefaultTranslationServiceStub::AsyncCreateGlossary(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions,
    google::cloud::translation::v3::CreateGlossaryRequest const& request) {
  return internal::MakeUnaryRpcImpl<
      google::cloud::translation::v3::CreateGlossaryRequest,
      google::longrunning::Operation>(
      cq,
      [this](
          grpc::ClientContext* context,
          google::cloud::translation::v3::CreateGlossaryRequest const& request,
          grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncCreateGlossary(context, request, cq);
      },
      request, std::move(context));
}

StatusOr<google::cloud::translation::v3::ListGlossariesResponse>
DefaultTranslationServiceStub::ListGlossaries(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::ListGlossariesRequest const& request) {
  google::cloud::translation::v3::ListGlossariesResponse response;
  auto status = grpc_stub_->ListGlossaries(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::translation::v3::Glossary>
DefaultTranslationServiceStub::GetGlossary(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::GetGlossaryRequest const& request) {
  google::cloud::translation::v3::Glossary response;
  auto status = grpc_stub_->GetGlossary(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

future<StatusOr<google::longrunning::Operation>>
DefaultTranslationServiceStub::AsyncDeleteGlossary(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions,
    google::cloud::translation::v3::DeleteGlossaryRequest const& request) {
  return internal::MakeUnaryRpcImpl<
      google::cloud::translation::v3::DeleteGlossaryRequest,
      google::longrunning::Operation>(
      cq,
      [this](
          grpc::ClientContext* context,
          google::cloud::translation::v3::DeleteGlossaryRequest const& request,
          grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncDeleteGlossary(context, request, cq);
      },
      request, std::move(context));
}

StatusOr<google::cloud::translation::v3::AdaptiveMtDataset>
DefaultTranslationServiceStub::CreateAdaptiveMtDataset(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::CreateAdaptiveMtDatasetRequest const&
        request) {
  google::cloud::translation::v3::AdaptiveMtDataset response;
  auto status =
      grpc_stub_->CreateAdaptiveMtDataset(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

Status DefaultTranslationServiceStub::DeleteAdaptiveMtDataset(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::DeleteAdaptiveMtDatasetRequest const&
        request) {
  google::protobuf::Empty response;
  auto status =
      grpc_stub_->DeleteAdaptiveMtDataset(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}

StatusOr<google::cloud::translation::v3::AdaptiveMtDataset>
DefaultTranslationServiceStub::GetAdaptiveMtDataset(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::GetAdaptiveMtDatasetRequest const&
        request) {
  google::cloud::translation::v3::AdaptiveMtDataset response;
  auto status = grpc_stub_->GetAdaptiveMtDataset(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::translation::v3::ListAdaptiveMtDatasetsResponse>
DefaultTranslationServiceStub::ListAdaptiveMtDatasets(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::ListAdaptiveMtDatasetsRequest const&
        request) {
  google::cloud::translation::v3::ListAdaptiveMtDatasetsResponse response;
  auto status =
      grpc_stub_->ListAdaptiveMtDatasets(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::translation::v3::AdaptiveMtTranslateResponse>
DefaultTranslationServiceStub::AdaptiveMtTranslate(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::AdaptiveMtTranslateRequest const& request) {
  google::cloud::translation::v3::AdaptiveMtTranslateResponse response;
  auto status = grpc_stub_->AdaptiveMtTranslate(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::translation::v3::AdaptiveMtFile>
DefaultTranslationServiceStub::GetAdaptiveMtFile(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::GetAdaptiveMtFileRequest const& request) {
  google::cloud::translation::v3::AdaptiveMtFile response;
  auto status = grpc_stub_->GetAdaptiveMtFile(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

Status DefaultTranslationServiceStub::DeleteAdaptiveMtFile(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::DeleteAdaptiveMtFileRequest const&
        request) {
  google::protobuf::Empty response;
  auto status = grpc_stub_->DeleteAdaptiveMtFile(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}

StatusOr<google::cloud::translation::v3::ImportAdaptiveMtFileResponse>
DefaultTranslationServiceStub::ImportAdaptiveMtFile(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::ImportAdaptiveMtFileRequest const&
        request) {
  google::cloud::translation::v3::ImportAdaptiveMtFileResponse response;
  auto status = grpc_stub_->ImportAdaptiveMtFile(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::translation::v3::ListAdaptiveMtFilesResponse>
DefaultTranslationServiceStub::ListAdaptiveMtFiles(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::ListAdaptiveMtFilesRequest const& request) {
  google::cloud::translation::v3::ListAdaptiveMtFilesResponse response;
  auto status = grpc_stub_->ListAdaptiveMtFiles(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::translation::v3::ListAdaptiveMtSentencesResponse>
DefaultTranslationServiceStub::ListAdaptiveMtSentences(
    grpc::ClientContext& context, Options const&,
    google::cloud::translation::v3::ListAdaptiveMtSentencesRequest const&
        request) {
  google::cloud::translation::v3::ListAdaptiveMtSentencesResponse response;
  auto status =
      grpc_stub_->ListAdaptiveMtSentences(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

future<StatusOr<google::longrunning::Operation>>
DefaultTranslationServiceStub::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    google::cloud::internal::ImmutableOptions,
    google::longrunning::GetOperationRequest const& request) {
  return internal::MakeUnaryRpcImpl<google::longrunning::GetOperationRequest,
                                    google::longrunning::Operation>(
      cq,
      [this](grpc::ClientContext* context,
             google::longrunning::GetOperationRequest const& request,
             grpc::CompletionQueue* cq) {
        return operations_->AsyncGetOperation(context, request, cq);
      },
      request, std::move(context));
}

future<Status> DefaultTranslationServiceStub::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    google::cloud::internal::ImmutableOptions,
    google::longrunning::CancelOperationRequest const& request) {
  return internal::MakeUnaryRpcImpl<google::longrunning::CancelOperationRequest,
                                    google::protobuf::Empty>(
             cq,
             [this](grpc::ClientContext* context,
                    google::longrunning::CancelOperationRequest const& request,
                    grpc::CompletionQueue* cq) {
               return operations_->AsyncCancelOperation(context, request, cq);
             },
             request, std::move(context))
      .then([](future<StatusOr<google::protobuf::Empty>> f) {
        return f.get().status();
      });
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace translate_v3_internal
}  // namespace cloud
}  // namespace google
