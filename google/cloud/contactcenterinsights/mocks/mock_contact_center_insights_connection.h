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
// source: google/cloud/contactcenterinsights/v1/contact_center_insights.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CONTACTCENTERINSIGHTS_MOCKS_MOCK_CONTACT_CENTER_INSIGHTS_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CONTACTCENTERINSIGHTS_MOCKS_MOCK_CONTACT_CENTER_INSIGHTS_CONNECTION_H

#include "google/cloud/contactcenterinsights/contact_center_insights_connection.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace contactcenterinsights_mocks {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * A class to mock `ContactCenterInsightsConnection`.
 *
 * Application developers may want to test their code with simulated responses,
 * including errors, from an object of type `ContactCenterInsightsClient`. To do
 * so, construct an object of type `ContactCenterInsightsClient` with an
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
class MockContactCenterInsightsConnection
    : public contactcenterinsights::ContactCenterInsightsConnection {
 public:
  MOCK_METHOD(Options, options, (), (override));

  MOCK_METHOD(StatusOr<google::cloud::contactcenterinsights::v1::Conversation>,
              CreateConversation,
              (google::cloud::contactcenterinsights::v1::
                   CreateConversationRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::cloud::contactcenterinsights::v1::Conversation>,
              UpdateConversation,
              (google::cloud::contactcenterinsights::v1::
                   UpdateConversationRequest const& request),
              (override));

  MOCK_METHOD(
      StatusOr<google::cloud::contactcenterinsights::v1::Conversation>,
      GetConversation,
      (google::cloud::contactcenterinsights::v1::GetConversationRequest const&
           request),
      (override));

  MOCK_METHOD(
      StreamRange<google::cloud::contactcenterinsights::v1::Conversation>,
      ListConversations,
      (google::cloud::contactcenterinsights::v1::ListConversationsRequest
           request),
      (override));

  MOCK_METHOD(Status, DeleteConversation,
              (google::cloud::contactcenterinsights::v1::
                   DeleteConversationRequest const& request),
              (override));

  MOCK_METHOD(
      future<StatusOr<google::cloud::contactcenterinsights::v1::Analysis>>,
      CreateAnalysis,
      (google::cloud::contactcenterinsights::v1::CreateAnalysisRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::contactcenterinsights::v1::Analysis>, GetAnalysis,
      (google::cloud::contactcenterinsights::v1::GetAnalysisRequest const&
           request),
      (override));

  MOCK_METHOD(
      StreamRange<google::cloud::contactcenterinsights::v1::Analysis>,
      ListAnalyses,
      (google::cloud::contactcenterinsights::v1::ListAnalysesRequest request),
      (override));

  MOCK_METHOD(
      Status, DeleteAnalysis,
      (google::cloud::contactcenterinsights::v1::DeleteAnalysisRequest const&
           request),
      (override));

  MOCK_METHOD(future<StatusOr<google::cloud::contactcenterinsights::v1::
                                  ExportInsightsDataResponse>>,
              ExportInsightsData,
              (google::cloud::contactcenterinsights::v1::
                   ExportInsightsDataRequest const& request),
              (override));

  MOCK_METHOD(
      future<StatusOr<google::cloud::contactcenterinsights::v1::IssueModel>>,
      CreateIssueModel,
      (google::cloud::contactcenterinsights::v1::CreateIssueModelRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::contactcenterinsights::v1::IssueModel>,
      UpdateIssueModel,
      (google::cloud::contactcenterinsights::v1::UpdateIssueModelRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::contactcenterinsights::v1::IssueModel>,
      GetIssueModel,
      (google::cloud::contactcenterinsights::v1::GetIssueModelRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<
          google::cloud::contactcenterinsights::v1::ListIssueModelsResponse>,
      ListIssueModels,
      (google::cloud::contactcenterinsights::v1::ListIssueModelsRequest const&
           request),
      (override));

  MOCK_METHOD(
      future<StatusOr<
          google::cloud::contactcenterinsights::v1::DeleteIssueModelMetadata>>,
      DeleteIssueModel,
      (google::cloud::contactcenterinsights::v1::DeleteIssueModelRequest const&
           request),
      (override));

  MOCK_METHOD(
      future<StatusOr<
          google::cloud::contactcenterinsights::v1::DeployIssueModelResponse>>,
      DeployIssueModel,
      (google::cloud::contactcenterinsights::v1::DeployIssueModelRequest const&
           request),
      (override));

  MOCK_METHOD(future<StatusOr<google::cloud::contactcenterinsights::v1::
                                  UndeployIssueModelResponse>>,
              UndeployIssueModel,
              (google::cloud::contactcenterinsights::v1::
                   UndeployIssueModelRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::cloud::contactcenterinsights::v1::Issue>,
              GetIssue,
              (google::cloud::contactcenterinsights::v1::GetIssueRequest const&
                   request),
              (override));

  MOCK_METHOD(
      StatusOr<google::cloud::contactcenterinsights::v1::ListIssuesResponse>,
      ListIssues,
      (google::cloud::contactcenterinsights::v1::ListIssuesRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::contactcenterinsights::v1::Issue>, UpdateIssue,
      (google::cloud::contactcenterinsights::v1::UpdateIssueRequest const&
           request),
      (override));

  MOCK_METHOD(StatusOr<google::cloud::contactcenterinsights::v1::
                           CalculateIssueModelStatsResponse>,
              CalculateIssueModelStats,
              (google::cloud::contactcenterinsights::v1::
                   CalculateIssueModelStatsRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::cloud::contactcenterinsights::v1::PhraseMatcher>,
              CreatePhraseMatcher,
              (google::cloud::contactcenterinsights::v1::
                   CreatePhraseMatcherRequest const& request),
              (override));

  MOCK_METHOD(
      StatusOr<google::cloud::contactcenterinsights::v1::PhraseMatcher>,
      GetPhraseMatcher,
      (google::cloud::contactcenterinsights::v1::GetPhraseMatcherRequest const&
           request),
      (override));

  MOCK_METHOD(
      StreamRange<google::cloud::contactcenterinsights::v1::PhraseMatcher>,
      ListPhraseMatchers,
      (google::cloud::contactcenterinsights::v1::ListPhraseMatchersRequest
           request),
      (override));

  MOCK_METHOD(Status, DeletePhraseMatcher,
              (google::cloud::contactcenterinsights::v1::
                   DeletePhraseMatcherRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::cloud::contactcenterinsights::v1::PhraseMatcher>,
              UpdatePhraseMatcher,
              (google::cloud::contactcenterinsights::v1::
                   UpdatePhraseMatcherRequest const& request),
              (override));

  MOCK_METHOD(
      StatusOr<
          google::cloud::contactcenterinsights::v1::CalculateStatsResponse>,
      CalculateStats,
      (google::cloud::contactcenterinsights::v1::CalculateStatsRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::contactcenterinsights::v1::Settings>, GetSettings,
      (google::cloud::contactcenterinsights::v1::GetSettingsRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::contactcenterinsights::v1::Settings>,
      UpdateSettings,
      (google::cloud::contactcenterinsights::v1::UpdateSettingsRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::contactcenterinsights::v1::View>, CreateView,
      (google::cloud::contactcenterinsights::v1::CreateViewRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::contactcenterinsights::v1::View>, GetView,
      (google::cloud::contactcenterinsights::v1::GetViewRequest const& request),
      (override));

  MOCK_METHOD(
      StreamRange<google::cloud::contactcenterinsights::v1::View>, ListViews,
      (google::cloud::contactcenterinsights::v1::ListViewsRequest request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::contactcenterinsights::v1::View>, UpdateView,
      (google::cloud::contactcenterinsights::v1::UpdateViewRequest const&
           request),
      (override));

  MOCK_METHOD(
      Status, DeleteView,
      (google::cloud::contactcenterinsights::v1::DeleteViewRequest const&
           request),
      (override));
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace contactcenterinsights_mocks
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CONTACTCENTERINSIGHTS_MOCKS_MOCK_CONTACT_CENTER_INSIGHTS_CONNECTION_H
