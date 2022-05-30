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
// source: google/cloud/functions/v1/functions.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_FUNCTIONS_MOCKS_MOCK_CLOUD_FUNCTIONS_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_FUNCTIONS_MOCKS_MOCK_CLOUD_FUNCTIONS_CONNECTION_H

#include "google/cloud/functions/cloud_functions_connection.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace functions_mocks {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * A class to mock `CloudFunctionsServiceConnection`.
 *
 * Application developers may want to test their code with simulated responses,
 * including errors, from an object of type `CloudFunctionsServiceClient`. To do
 * so, construct an object of type `CloudFunctionsServiceClient` with an
 * instance of this class. Then use the Google Test framework functions to
 * program the behavior of this mock.
 *
 * @see [This example][bq-mock] for how to test your application with
 * GoogleTest. While the example showcases types from the BigQuery library, the
 * underlying principles apply for any pair of `*Client` and `*Connection`.
 *
 * [bq-mock]:
 * https://googleapis.dev/cpp/google-cloud-bigquery/latest/bigquery-read-mock.html
 */
class MockCloudFunctionsServiceConnection
    : public functions::CloudFunctionsServiceConnection {
 public:
  MOCK_METHOD(Options, options, (), (override));

  MOCK_METHOD(StreamRange<google::cloud::functions::v1::CloudFunction>,
              ListFunctions,
              (google::cloud::functions::v1::ListFunctionsRequest request),
              (override));

  MOCK_METHOD(StatusOr<google::cloud::functions::v1::CloudFunction>,
              GetFunction,
              (google::cloud::functions::v1::GetFunctionRequest const& request),
              (override));

  MOCK_METHOD(
      future<StatusOr<google::cloud::functions::v1::CloudFunction>>,
      CreateFunction,
      (google::cloud::functions::v1::CreateFunctionRequest const& request),
      (override));

  MOCK_METHOD(
      future<StatusOr<google::cloud::functions::v1::CloudFunction>>,
      UpdateFunction,
      (google::cloud::functions::v1::UpdateFunctionRequest const& request),
      (override));

  MOCK_METHOD(
      future<StatusOr<google::cloud::functions::v1::OperationMetadataV1>>,
      DeleteFunction,
      (google::cloud::functions::v1::DeleteFunctionRequest const& request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::functions::v1::CallFunctionResponse>,
      CallFunction,
      (google::cloud::functions::v1::CallFunctionRequest const& request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::functions::v1::GenerateUploadUrlResponse>,
      GenerateUploadUrl,
      (google::cloud::functions::v1::GenerateUploadUrlRequest const& request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::functions::v1::GenerateDownloadUrlResponse>,
      GenerateDownloadUrl,
      (google::cloud::functions::v1::GenerateDownloadUrlRequest const& request),
      (override));

  MOCK_METHOD(StatusOr<google::iam::v1::Policy>, SetIamPolicy,
              (google::iam::v1::SetIamPolicyRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::iam::v1::Policy>, GetIamPolicy,
              (google::iam::v1::GetIamPolicyRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::iam::v1::TestIamPermissionsResponse>,
              TestIamPermissions,
              (google::iam::v1::TestIamPermissionsRequest const& request),
              (override));
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace functions_mocks
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_FUNCTIONS_MOCKS_MOCK_CLOUD_FUNCTIONS_CONNECTION_H
