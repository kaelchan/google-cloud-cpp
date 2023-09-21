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
// google/cloud/compute/interconnect_attachments/v1/interconnect_attachments.proto

#include "google/cloud/compute/interconnect_attachments/v1/interconnect_attachments_rest_connection.h"
#include "google/cloud/compute/interconnect_attachments/v1/interconnect_attachments_options.h"
#include "google/cloud/compute/interconnect_attachments/v1/internal/interconnect_attachments_option_defaults.h"
#include "google/cloud/compute/interconnect_attachments/v1/internal/interconnect_attachments_rest_connection_impl.h"
#include "google/cloud/compute/interconnect_attachments/v1/internal/interconnect_attachments_rest_stub_factory.h"
#include "google/cloud/compute/interconnect_attachments/v1/internal/interconnect_attachments_tracing_connection.h"
#include "google/cloud/common_options.h"
#include "google/cloud/credentials.h"
#include "google/cloud/internal/rest_background_threads_impl.h"
#include <memory>

namespace google {
namespace cloud {
namespace compute_interconnect_attachments_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<InterconnectAttachmentsConnection>
MakeInterconnectAttachmentsConnectionRest(Options options) {
  internal::CheckExpectedOptions<CommonOptionList, RestOptionList,
                                 UnifiedCredentialsOptionList,
                                 InterconnectAttachmentsPolicyOptionList>(
      options, __func__);
  options = compute_interconnect_attachments_v1_internal::
      InterconnectAttachmentsDefaultOptions(std::move(options));
  auto background = std::make_unique<
      rest_internal::AutomaticallyCreatedRestBackgroundThreads>();
  auto stub = compute_interconnect_attachments_v1_internal::
      CreateDefaultInterconnectAttachmentsRestStub(options);
  return compute_interconnect_attachments_v1_internal::
      MakeInterconnectAttachmentsTracingConnection(
          std::make_shared<compute_interconnect_attachments_v1_internal::
                               InterconnectAttachmentsRestConnectionImpl>(
              std::move(background), std::move(stub), std::move(options)));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_interconnect_attachments_v1
}  // namespace cloud
}  // namespace google
