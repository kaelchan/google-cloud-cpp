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
// source: google/cloud/compute/http_health_checks/v1/http_health_checks.proto

#include "google/cloud/compute/http_health_checks/v1/http_health_checks_client.h"
#include <memory>

namespace google {
namespace cloud {
namespace compute_http_health_checks_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

HttpHealthChecksClient::HttpHealthChecksClient(
    std::shared_ptr<HttpHealthChecksConnection> connection, Options opts)
    : connection_(std::move(connection)),
      options_(
          internal::MergeOptions(std::move(opts), connection_->options())) {}
HttpHealthChecksClient::~HttpHealthChecksClient() = default;

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
HttpHealthChecksClient::DeleteHttpHealthCheck(
    std::string const& project, std::string const& http_health_check,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::http_health_checks::v1::
      DeleteHttpHealthCheckRequest request;
  request.set_project(project);
  request.set_http_health_check(http_health_check);
  return connection_->DeleteHttpHealthCheck(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
HttpHealthChecksClient::DeleteHttpHealthCheck(
    google::cloud::cpp::compute::http_health_checks::v1::
        DeleteHttpHealthCheckRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteHttpHealthCheck(request);
}

StatusOr<google::cloud::cpp::compute::v1::HttpHealthCheck>
HttpHealthChecksClient::GetHttpHealthCheck(std::string const& project,
                                           std::string const& http_health_check,
                                           Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::http_health_checks::v1::GetHttpHealthCheckRequest
      request;
  request.set_project(project);
  request.set_http_health_check(http_health_check);
  return connection_->GetHttpHealthCheck(request);
}

StatusOr<google::cloud::cpp::compute::v1::HttpHealthCheck>
HttpHealthChecksClient::GetHttpHealthCheck(
    google::cloud::cpp::compute::http_health_checks::v1::
        GetHttpHealthCheckRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetHttpHealthCheck(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
HttpHealthChecksClient::InsertHttpHealthCheck(
    std::string const& project,
    google::cloud::cpp::compute::v1::HttpHealthCheck const&
        http_health_check_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::http_health_checks::v1::
      InsertHttpHealthCheckRequest request;
  request.set_project(project);
  *request.mutable_http_health_check_resource() = http_health_check_resource;
  return connection_->InsertHttpHealthCheck(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
HttpHealthChecksClient::InsertHttpHealthCheck(
    google::cloud::cpp::compute::http_health_checks::v1::
        InsertHttpHealthCheckRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->InsertHttpHealthCheck(request);
}

StreamRange<google::cloud::cpp::compute::v1::HttpHealthCheck>
HttpHealthChecksClient::ListHttpHealthChecks(std::string const& project,
                                             Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::http_health_checks::v1::
      ListHttpHealthChecksRequest request;
  request.set_project(project);
  return connection_->ListHttpHealthChecks(request);
}

StreamRange<google::cloud::cpp::compute::v1::HttpHealthCheck>
HttpHealthChecksClient::ListHttpHealthChecks(
    google::cloud::cpp::compute::http_health_checks::v1::
        ListHttpHealthChecksRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListHttpHealthChecks(std::move(request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
HttpHealthChecksClient::PatchHttpHealthCheck(
    std::string const& project, std::string const& http_health_check,
    google::cloud::cpp::compute::v1::HttpHealthCheck const&
        http_health_check_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::http_health_checks::v1::
      PatchHttpHealthCheckRequest request;
  request.set_project(project);
  request.set_http_health_check(http_health_check);
  *request.mutable_http_health_check_resource() = http_health_check_resource;
  return connection_->PatchHttpHealthCheck(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
HttpHealthChecksClient::PatchHttpHealthCheck(
    google::cloud::cpp::compute::http_health_checks::v1::
        PatchHttpHealthCheckRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->PatchHttpHealthCheck(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
HttpHealthChecksClient::UpdateHttpHealthCheck(
    std::string const& project, std::string const& http_health_check,
    google::cloud::cpp::compute::v1::HttpHealthCheck const&
        http_health_check_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::http_health_checks::v1::
      UpdateHttpHealthCheckRequest request;
  request.set_project(project);
  request.set_http_health_check(http_health_check);
  *request.mutable_http_health_check_resource() = http_health_check_resource;
  return connection_->UpdateHttpHealthCheck(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
HttpHealthChecksClient::UpdateHttpHealthCheck(
    google::cloud::cpp::compute::http_health_checks::v1::
        UpdateHttpHealthCheckRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateHttpHealthCheck(request);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_http_health_checks_v1
}  // namespace cloud
}  // namespace google
