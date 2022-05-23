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
// source: google/cloud/memcache/v1/cloud_memcache.proto

#include "google/cloud/memcache/internal/cloud_memcache_option_defaults.h"
#include "google/cloud/memcache/cloud_memcache_connection.h"
#include "google/cloud/memcache/cloud_memcache_options.h"
#include "google/cloud/internal/populate_common_options.h"
#include "google/cloud/internal/populate_grpc_options.h"
#include <memory>

namespace google {
namespace cloud {
namespace memcache_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

namespace {
auto constexpr kBackoffScaling = 2.0;
}  // namespace

Options CloudMemcacheDefaultOptions(Options options) {
  options = google::cloud::internal::PopulateCommonOptions(
      std::move(options), "GOOGLE_CLOUD_CPP_CLOUD_MEMCACHE_ENDPOINT", "",
      "GOOGLE_CLOUD_CPP_CLOUD_MEMCACHE_AUTHORITY", "memcache.googleapis.com");
  options =
      google::cloud::internal::PopulateGrpcOptions(std::move(options), "");
  if (!options.has<memcache::CloudMemcacheRetryPolicyOption>()) {
    options.set<memcache::CloudMemcacheRetryPolicyOption>(
        memcache::CloudMemcacheLimitedTimeRetryPolicy(std::chrono::minutes(30))
            .clone());
  }
  if (!options.has<memcache::CloudMemcacheBackoffPolicyOption>()) {
    options.set<memcache::CloudMemcacheBackoffPolicyOption>(
        ExponentialBackoffPolicy(std::chrono::seconds(1),
                                 std::chrono::minutes(5), kBackoffScaling)
            .clone());
  }
  if (!options.has<memcache::CloudMemcachePollingPolicyOption>()) {
    options.set<memcache::CloudMemcachePollingPolicyOption>(
        GenericPollingPolicy<memcache::CloudMemcacheRetryPolicyOption::Type,
                             memcache::CloudMemcacheBackoffPolicyOption::Type>(
            options.get<memcache::CloudMemcacheRetryPolicyOption>()->clone(),
            options.get<memcache::CloudMemcacheBackoffPolicyOption>()->clone())
            .clone());
  }
  if (!options
           .has<memcache::CloudMemcacheConnectionIdempotencyPolicyOption>()) {
    options.set<memcache::CloudMemcacheConnectionIdempotencyPolicyOption>(
        memcache::MakeDefaultCloudMemcacheConnectionIdempotencyPolicy());
  }

  return options;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace memcache_internal
}  // namespace cloud
}  // namespace google
