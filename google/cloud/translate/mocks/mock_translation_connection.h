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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TRANSLATE_MOCKS_MOCK_TRANSLATION_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TRANSLATE_MOCKS_MOCK_TRANSLATION_CONNECTION_H

#include "google/cloud/translate/translation_connection.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace translate_mocks {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * A class to mock `TranslationServiceConnection`.
 *
 * Application developers may want to test their code with simulated responses,
 * including errors, from an object of type `TranslationServiceClient`. To do
 * so, construct an object of type `TranslationServiceClient` with an instance
 * of this class. Then use the Google Test framework functions to program the
 * behavior of this mock.
 *
 * @see [This example][bq-mock] for how to test your application with
 * GoogleTest. While the example showcases types from the BigQuery library, the
 * underlying principles apply for any pair of `*Client` and `*Connection`.
 *
 * [bq-mock]:
 * https://googleapis.dev/cpp/google-cloud-bigquery/latest/bigquery-read-mock.html
 */
class MockTranslationServiceConnection
    : public translate::TranslationServiceConnection {
 public:
  MOCK_METHOD(Options, options, (), (override));

  MOCK_METHOD(
      StatusOr<google::cloud::translation::v3::TranslateTextResponse>,
      TranslateText,
      (google::cloud::translation::v3::TranslateTextRequest const& request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::translation::v3::DetectLanguageResponse>,
      DetectLanguage,
      (google::cloud::translation::v3::DetectLanguageRequest const& request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::translation::v3::SupportedLanguages>,
      GetSupportedLanguages,
      (google::cloud::translation::v3::GetSupportedLanguagesRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::translation::v3::TranslateDocumentResponse>,
      TranslateDocument,
      (google::cloud::translation::v3::TranslateDocumentRequest const& request),
      (override));

  MOCK_METHOD(
      future<StatusOr<google::cloud::translation::v3::BatchTranslateResponse>>,
      BatchTranslateText,
      (google::cloud::translation::v3::BatchTranslateTextRequest const&
           request),
      (override));

  MOCK_METHOD(
      future<StatusOr<
          google::cloud::translation::v3::BatchTranslateDocumentResponse>>,
      BatchTranslateDocument,
      (google::cloud::translation::v3::BatchTranslateDocumentRequest const&
           request),
      (override));

  MOCK_METHOD(
      future<StatusOr<google::cloud::translation::v3::Glossary>>,
      CreateGlossary,
      (google::cloud::translation::v3::CreateGlossaryRequest const& request),
      (override));

  MOCK_METHOD(StreamRange<google::cloud::translation::v3::Glossary>,
              ListGlossaries,
              (google::cloud::translation::v3::ListGlossariesRequest request),
              (override));

  MOCK_METHOD(
      StatusOr<google::cloud::translation::v3::Glossary>, GetGlossary,
      (google::cloud::translation::v3::GetGlossaryRequest const& request),
      (override));

  MOCK_METHOD(
      future<StatusOr<google::cloud::translation::v3::DeleteGlossaryResponse>>,
      DeleteGlossary,
      (google::cloud::translation::v3::DeleteGlossaryRequest const& request),
      (override));
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace translate_mocks
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TRANSLATE_MOCKS_MOCK_TRANSLATION_CONNECTION_H
