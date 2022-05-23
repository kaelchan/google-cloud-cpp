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
// source: google/cloud/shell/v1/cloudshell.proto

#include "google/cloud/shell/internal/cloud_shell_option_defaults.h"
#include "google/cloud/shell/cloud_shell_connection.h"
#include "google/cloud/shell/cloud_shell_options.h"
#include "google/cloud/internal/populate_common_options.h"
#include "google/cloud/internal/populate_grpc_options.h"
#include <memory>

namespace google {
namespace cloud {
namespace shell_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

namespace {
auto constexpr kBackoffScaling = 2.0;
}  // namespace

Options CloudShellServiceDefaultOptions(Options options) {
  options = google::cloud::internal::PopulateCommonOptions(
      std::move(options), "GOOGLE_CLOUD_CPP_CLOUD_SHELL_SERVICE_ENDPOINT", "",
      "GOOGLE_CLOUD_CPP_CLOUD_SHELL_SERVICE_AUTHORITY",
      "cloudshell.googleapis.com");
  options =
      google::cloud::internal::PopulateGrpcOptions(std::move(options), "");
  if (!options.has<shell::CloudShellServiceRetryPolicyOption>()) {
    options.set<shell::CloudShellServiceRetryPolicyOption>(
        shell::CloudShellServiceLimitedTimeRetryPolicy(std::chrono::minutes(30))
            .clone());
  }
  if (!options.has<shell::CloudShellServiceBackoffPolicyOption>()) {
    options.set<shell::CloudShellServiceBackoffPolicyOption>(
        ExponentialBackoffPolicy(std::chrono::seconds(1),
                                 std::chrono::minutes(5), kBackoffScaling)
            .clone());
  }
  if (!options.has<shell::CloudShellServicePollingPolicyOption>()) {
    options.set<shell::CloudShellServicePollingPolicyOption>(
        GenericPollingPolicy<shell::CloudShellServiceRetryPolicyOption::Type,
                             shell::CloudShellServiceBackoffPolicyOption::Type>(
            options.get<shell::CloudShellServiceRetryPolicyOption>()->clone(),
            options.get<shell::CloudShellServiceBackoffPolicyOption>()->clone())
            .clone());
  }
  if (!options
           .has<shell::CloudShellServiceConnectionIdempotencyPolicyOption>()) {
    options.set<shell::CloudShellServiceConnectionIdempotencyPolicyOption>(
        shell::MakeDefaultCloudShellServiceConnectionIdempotencyPolicy());
  }

  return options;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace shell_internal
}  // namespace cloud
}  // namespace google
