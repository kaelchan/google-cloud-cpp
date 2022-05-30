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
// source: google/cloud/billing/v1/cloud_catalog.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BILLING_MOCKS_MOCK_CLOUD_CATALOG_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BILLING_MOCKS_MOCK_CLOUD_CATALOG_CONNECTION_H

#include "google/cloud/billing/cloud_catalog_connection.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace billing_mocks {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * A class to mock `CloudCatalogConnection`.
 *
 * Application developers may want to test their code with simulated responses,
 * including errors, from an object of type `CloudCatalogClient`. To do so,
 * construct an object of type `CloudCatalogClient` with an instance of this
 * class. Then use the Google Test framework functions to program the behavior
 * of this mock.
 *
 * @see [This example][bq-mock] for how to test your application with
 * GoogleTest. While the example showcases types from the BigQuery library, the
 * underlying principles apply for any pair of `*Client` and `*Connection`.
 *
 * [bq-mock]:
 * https://googleapis.dev/cpp/google-cloud-bigquery/latest/bigquery-read-mock.html
 */
class MockCloudCatalogConnection : public billing::CloudCatalogConnection {
 public:
  MOCK_METHOD(Options, options, (), (override));

  MOCK_METHOD(StreamRange<google::cloud::billing::v1::Service>, ListServices,
              (google::cloud::billing::v1::ListServicesRequest request),
              (override));

  MOCK_METHOD(StreamRange<google::cloud::billing::v1::Sku>, ListSkus,
              (google::cloud::billing::v1::ListSkusRequest request),
              (override));
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace billing_mocks
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BILLING_MOCKS_MOCK_CLOUD_CATALOG_CONNECTION_H
