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
// google/cloud/compute/region_ssl_certificates/v1/region_ssl_certificates.proto

#include "google/cloud/compute/region_ssl_certificates/v1/region_ssl_certificates_client.h"
#include <memory>

namespace google {
namespace cloud {
namespace compute_region_ssl_certificates_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

RegionSslCertificatesClient::RegionSslCertificatesClient(
    std::shared_ptr<RegionSslCertificatesConnection> connection, Options opts)
    : connection_(std::move(connection)),
      options_(
          internal::MergeOptions(std::move(opts), connection_->options())) {}
RegionSslCertificatesClient::~RegionSslCertificatesClient() = default;

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
RegionSslCertificatesClient::DeleteSslCertificate(
    std::string const& project, std::string const& region,
    std::string const& ssl_certificate, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::region_ssl_certificates::v1::
      DeleteSslCertificateRequest request;
  request.set_project(project);
  request.set_region(region);
  request.set_ssl_certificate(ssl_certificate);
  return connection_->DeleteSslCertificate(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
RegionSslCertificatesClient::DeleteSslCertificate(
    google::cloud::cpp::compute::region_ssl_certificates::v1::
        DeleteSslCertificateRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteSslCertificate(request);
}

StatusOr<google::cloud::cpp::compute::v1::SslCertificate>
RegionSslCertificatesClient::GetSslCertificate(
    std::string const& project, std::string const& region,
    std::string const& ssl_certificate, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::region_ssl_certificates::v1::
      GetSslCertificateRequest request;
  request.set_project(project);
  request.set_region(region);
  request.set_ssl_certificate(ssl_certificate);
  return connection_->GetSslCertificate(request);
}

StatusOr<google::cloud::cpp::compute::v1::SslCertificate>
RegionSslCertificatesClient::GetSslCertificate(
    google::cloud::cpp::compute::region_ssl_certificates::v1::
        GetSslCertificateRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetSslCertificate(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
RegionSslCertificatesClient::InsertSslCertificate(
    std::string const& project, std::string const& region,
    google::cloud::cpp::compute::v1::SslCertificate const&
        ssl_certificate_resource,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::region_ssl_certificates::v1::
      InsertSslCertificateRequest request;
  request.set_project(project);
  request.set_region(region);
  *request.mutable_ssl_certificate_resource() = ssl_certificate_resource;
  return connection_->InsertSslCertificate(request);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
RegionSslCertificatesClient::InsertSslCertificate(
    google::cloud::cpp::compute::region_ssl_certificates::v1::
        InsertSslCertificateRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->InsertSslCertificate(request);
}

StreamRange<google::cloud::cpp::compute::v1::SslCertificate>
RegionSslCertificatesClient::ListRegionSslCertificates(
    std::string const& project, std::string const& region, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::cpp::compute::region_ssl_certificates::v1::
      ListRegionSslCertificatesRequest request;
  request.set_project(project);
  request.set_region(region);
  return connection_->ListRegionSslCertificates(request);
}

StreamRange<google::cloud::cpp::compute::v1::SslCertificate>
RegionSslCertificatesClient::ListRegionSslCertificates(
    google::cloud::cpp::compute::region_ssl_certificates::v1::
        ListRegionSslCertificatesRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListRegionSslCertificates(std::move(request));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_region_ssl_certificates_v1
}  // namespace cloud
}  // namespace google
