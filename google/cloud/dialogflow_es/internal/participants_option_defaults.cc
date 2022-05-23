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
// source: google/cloud/dialogflow/v2/participant.proto

#include "google/cloud/dialogflow_es/internal/participants_option_defaults.h"
#include "google/cloud/dialogflow_es/participants_connection.h"
#include "google/cloud/dialogflow_es/participants_options.h"
#include "google/cloud/internal/populate_common_options.h"
#include "google/cloud/internal/populate_grpc_options.h"
#include <memory>

namespace google {
namespace cloud {
namespace dialogflow_es_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

namespace {
auto constexpr kBackoffScaling = 2.0;
}  // namespace

Options ParticipantsDefaultOptions(Options options) {
  options = google::cloud::internal::PopulateCommonOptions(
      std::move(options), "GOOGLE_CLOUD_CPP_PARTICIPANTS_ENDPOINT", "",
      "GOOGLE_CLOUD_CPP_PARTICIPANTS_AUTHORITY", "dialogflow.googleapis.com");
  options =
      google::cloud::internal::PopulateGrpcOptions(std::move(options), "");
  if (!options.has<dialogflow_es::ParticipantsRetryPolicyOption>()) {
    options.set<dialogflow_es::ParticipantsRetryPolicyOption>(
        dialogflow_es::ParticipantsLimitedTimeRetryPolicy(
            std::chrono::minutes(30))
            .clone());
  }
  if (!options.has<dialogflow_es::ParticipantsBackoffPolicyOption>()) {
    options.set<dialogflow_es::ParticipantsBackoffPolicyOption>(
        ExponentialBackoffPolicy(std::chrono::seconds(1),
                                 std::chrono::minutes(5), kBackoffScaling)
            .clone());
  }
  if (!options.has<
          dialogflow_es::ParticipantsConnectionIdempotencyPolicyOption>()) {
    options.set<dialogflow_es::ParticipantsConnectionIdempotencyPolicyOption>(
        dialogflow_es::MakeDefaultParticipantsConnectionIdempotencyPolicy());
  }

  return options;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dialogflow_es_internal
}  // namespace cloud
}  // namespace google
