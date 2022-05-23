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
// source: google/cloud/dataplex/v1/service.proto

#include "google/cloud/dataplex/internal/dataplex_option_defaults.h"
#include "google/cloud/dataplex/dataplex_connection.h"
#include "google/cloud/dataplex/dataplex_options.h"
#include "google/cloud/internal/populate_common_options.h"
#include "google/cloud/internal/populate_grpc_options.h"
#include <memory>

namespace google {
namespace cloud {
namespace dataplex_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

namespace {
auto constexpr kBackoffScaling = 2.0;
}  // namespace

Options DataplexServiceDefaultOptions(Options options) {
  options = google::cloud::internal::PopulateCommonOptions(
      std::move(options), "GOOGLE_CLOUD_CPP_DATAPLEX_SERVICE_ENDPOINT", "",
      "GOOGLE_CLOUD_CPP_DATAPLEX_SERVICE_AUTHORITY", "dataplex.googleapis.com");
  options =
      google::cloud::internal::PopulateGrpcOptions(std::move(options), "");
  if (!options.has<dataplex::DataplexServiceRetryPolicyOption>()) {
    options.set<dataplex::DataplexServiceRetryPolicyOption>(
        dataplex::DataplexServiceLimitedTimeRetryPolicy(
            std::chrono::minutes(30))
            .clone());
  }
  if (!options.has<dataplex::DataplexServiceBackoffPolicyOption>()) {
    options.set<dataplex::DataplexServiceBackoffPolicyOption>(
        ExponentialBackoffPolicy(std::chrono::seconds(1),
                                 std::chrono::minutes(5), kBackoffScaling)
            .clone());
  }
  if (!options.has<dataplex::DataplexServicePollingPolicyOption>()) {
    options.set<dataplex::DataplexServicePollingPolicyOption>(
        GenericPollingPolicy<
            dataplex::DataplexServiceRetryPolicyOption::Type,
            dataplex::DataplexServiceBackoffPolicyOption::Type>(
            options.get<dataplex::DataplexServiceRetryPolicyOption>()->clone(),
            options.get<dataplex::DataplexServiceBackoffPolicyOption>()
                ->clone())
            .clone());
  }
  if (!options
           .has<dataplex::DataplexServiceConnectionIdempotencyPolicyOption>()) {
    options.set<dataplex::DataplexServiceConnectionIdempotencyPolicyOption>(
        dataplex::MakeDefaultDataplexServiceConnectionIdempotencyPolicy());
  }

  return options;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dataplex_internal
}  // namespace cloud
}  // namespace google
