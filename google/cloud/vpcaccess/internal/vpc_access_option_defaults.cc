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
// source: google/cloud/vpcaccess/v1/vpc_access.proto

#include "google/cloud/vpcaccess/internal/vpc_access_option_defaults.h"
#include "google/cloud/vpcaccess/vpc_access_connection.h"
#include "google/cloud/vpcaccess/vpc_access_options.h"
#include "google/cloud/internal/populate_common_options.h"
#include "google/cloud/internal/populate_grpc_options.h"
#include <memory>

namespace google {
namespace cloud {
namespace vpcaccess_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

namespace {
auto constexpr kBackoffScaling = 2.0;
}  // namespace

Options VpcAccessServiceDefaultOptions(Options options) {
  options = google::cloud::internal::PopulateCommonOptions(
      std::move(options), "GOOGLE_CLOUD_CPP_VPC_ACCESS_SERVICE_ENDPOINT", "",
      "GOOGLE_CLOUD_CPP_VPC_ACCESS_SERVICE_AUTHORITY",
      "vpcaccess.googleapis.com");
  options =
      google::cloud::internal::PopulateGrpcOptions(std::move(options), "");
  if (!options.has<vpcaccess::VpcAccessServiceRetryPolicyOption>()) {
    options.set<vpcaccess::VpcAccessServiceRetryPolicyOption>(
        vpcaccess::VpcAccessServiceLimitedTimeRetryPolicy(
            std::chrono::minutes(30))
            .clone());
  }
  if (!options.has<vpcaccess::VpcAccessServiceBackoffPolicyOption>()) {
    options.set<vpcaccess::VpcAccessServiceBackoffPolicyOption>(
        ExponentialBackoffPolicy(std::chrono::seconds(1),
                                 std::chrono::minutes(5), kBackoffScaling)
            .clone());
  }
  if (!options.has<vpcaccess::VpcAccessServicePollingPolicyOption>()) {
    options.set<vpcaccess::VpcAccessServicePollingPolicyOption>(
        GenericPollingPolicy<
            vpcaccess::VpcAccessServiceRetryPolicyOption::Type,
            vpcaccess::VpcAccessServiceBackoffPolicyOption::Type>(
            options.get<vpcaccess::VpcAccessServiceRetryPolicyOption>()
                ->clone(),
            options.get<vpcaccess::VpcAccessServiceBackoffPolicyOption>()
                ->clone())
            .clone());
  }
  if (!options.has<
          vpcaccess::VpcAccessServiceConnectionIdempotencyPolicyOption>()) {
    options.set<vpcaccess::VpcAccessServiceConnectionIdempotencyPolicyOption>(
        vpcaccess::MakeDefaultVpcAccessServiceConnectionIdempotencyPolicy());
  }

  return options;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace vpcaccess_internal
}  // namespace cloud
}  // namespace google
