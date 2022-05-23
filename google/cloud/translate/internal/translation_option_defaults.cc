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

#include "google/cloud/translate/internal/translation_option_defaults.h"
#include "google/cloud/translate/translation_connection.h"
#include "google/cloud/translate/translation_options.h"
#include "google/cloud/internal/populate_common_options.h"
#include "google/cloud/internal/populate_grpc_options.h"
#include <memory>

namespace google {
namespace cloud {
namespace translate_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

namespace {
auto constexpr kBackoffScaling = 2.0;
}  // namespace

Options TranslationServiceDefaultOptions(Options options) {
  options = google::cloud::internal::PopulateCommonOptions(
      std::move(options), "GOOGLE_CLOUD_CPP_TRANSLATION_SERVICE_ENDPOINT", "",
      "GOOGLE_CLOUD_CPP_TRANSLATION_SERVICE_AUTHORITY",
      "translate.googleapis.com");
  options =
      google::cloud::internal::PopulateGrpcOptions(std::move(options), "");
  if (!options.has<translate::TranslationServiceRetryPolicyOption>()) {
    options.set<translate::TranslationServiceRetryPolicyOption>(
        translate::TranslationServiceLimitedTimeRetryPolicy(
            std::chrono::minutes(30))
            .clone());
  }
  if (!options.has<translate::TranslationServiceBackoffPolicyOption>()) {
    options.set<translate::TranslationServiceBackoffPolicyOption>(
        ExponentialBackoffPolicy(std::chrono::seconds(1),
                                 std::chrono::minutes(5), kBackoffScaling)
            .clone());
  }
  if (!options.has<translate::TranslationServicePollingPolicyOption>()) {
    options.set<translate::TranslationServicePollingPolicyOption>(
        GenericPollingPolicy<
            translate::TranslationServiceRetryPolicyOption::Type,
            translate::TranslationServiceBackoffPolicyOption::Type>(
            options.get<translate::TranslationServiceRetryPolicyOption>()
                ->clone(),
            options.get<translate::TranslationServiceBackoffPolicyOption>()
                ->clone())
            .clone());
  }
  if (!options.has<
          translate::TranslationServiceConnectionIdempotencyPolicyOption>()) {
    options.set<translate::TranslationServiceConnectionIdempotencyPolicyOption>(
        translate::MakeDefaultTranslationServiceConnectionIdempotencyPolicy());
  }

  return options;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace translate_internal
}  // namespace cloud
}  // namespace google
