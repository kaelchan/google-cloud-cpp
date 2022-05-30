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
// source: google/cloud/kms/v1/service.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_KMS_KEY_MANAGEMENT_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_KMS_KEY_MANAGEMENT_CONNECTION_H

#include "google/cloud/kms/internal/key_management_retry_traits.h"
#include "google/cloud/kms/internal/key_management_stub.h"
#include "google/cloud/kms/key_management_connection_idempotency_policy.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace kms {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using KeyManagementServiceRetryPolicy =
    ::google::cloud::internal::TraitBasedRetryPolicy<
        kms_internal::KeyManagementServiceRetryTraits>;

using KeyManagementServiceLimitedTimeRetryPolicy =
    ::google::cloud::internal::LimitedTimeRetryPolicy<
        kms_internal::KeyManagementServiceRetryTraits>;

using KeyManagementServiceLimitedErrorCountRetryPolicy =
    ::google::cloud::internal::LimitedErrorCountRetryPolicy<
        kms_internal::KeyManagementServiceRetryTraits>;

/**
 * The `KeyManagementServiceConnection` object for `KeyManagementServiceClient`.
 *
 * This interface defines virtual methods for each of the user-facing overload
 * sets in `KeyManagementServiceClient`. This allows users to inject custom
 * behavior (e.g., with a Google Mock object) when writing tests that use
 * objects of type `KeyManagementServiceClient`.
 *
 * To create a concrete instance, see `MakeKeyManagementServiceConnection()`.
 *
 * For mocking, see `kms_mocks::MockKeyManagementServiceConnection`.
 */
class KeyManagementServiceConnection {
 public:
  virtual ~KeyManagementServiceConnection() = 0;

  virtual Options options() { return Options{}; }

  virtual StreamRange<google::cloud::kms::v1::KeyRing> ListKeyRings(
      google::cloud::kms::v1::ListKeyRingsRequest request);

  virtual StreamRange<google::cloud::kms::v1::CryptoKey> ListCryptoKeys(
      google::cloud::kms::v1::ListCryptoKeysRequest request);

  virtual StreamRange<google::cloud::kms::v1::CryptoKeyVersion>
  ListCryptoKeyVersions(
      google::cloud::kms::v1::ListCryptoKeyVersionsRequest request);

  virtual StreamRange<google::cloud::kms::v1::ImportJob> ListImportJobs(
      google::cloud::kms::v1::ListImportJobsRequest request);

  virtual StatusOr<google::cloud::kms::v1::KeyRing> GetKeyRing(
      google::cloud::kms::v1::GetKeyRingRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::CryptoKey> GetCryptoKey(
      google::cloud::kms::v1::GetCryptoKeyRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::CryptoKeyVersion>
  GetCryptoKeyVersion(
      google::cloud::kms::v1::GetCryptoKeyVersionRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::PublicKey> GetPublicKey(
      google::cloud::kms::v1::GetPublicKeyRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::ImportJob> GetImportJob(
      google::cloud::kms::v1::GetImportJobRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::KeyRing> CreateKeyRing(
      google::cloud::kms::v1::CreateKeyRingRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::CryptoKey> CreateCryptoKey(
      google::cloud::kms::v1::CreateCryptoKeyRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::CryptoKeyVersion>
  CreateCryptoKeyVersion(
      google::cloud::kms::v1::CreateCryptoKeyVersionRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::CryptoKeyVersion>
  ImportCryptoKeyVersion(
      google::cloud::kms::v1::ImportCryptoKeyVersionRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::ImportJob> CreateImportJob(
      google::cloud::kms::v1::CreateImportJobRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::CryptoKey> UpdateCryptoKey(
      google::cloud::kms::v1::UpdateCryptoKeyRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::CryptoKeyVersion>
  UpdateCryptoKeyVersion(
      google::cloud::kms::v1::UpdateCryptoKeyVersionRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::CryptoKey>
  UpdateCryptoKeyPrimaryVersion(
      google::cloud::kms::v1::UpdateCryptoKeyPrimaryVersionRequest const&
          request);

  virtual StatusOr<google::cloud::kms::v1::CryptoKeyVersion>
  DestroyCryptoKeyVersion(
      google::cloud::kms::v1::DestroyCryptoKeyVersionRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::CryptoKeyVersion>
  RestoreCryptoKeyVersion(
      google::cloud::kms::v1::RestoreCryptoKeyVersionRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::EncryptResponse> Encrypt(
      google::cloud::kms::v1::EncryptRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::DecryptResponse> Decrypt(
      google::cloud::kms::v1::DecryptRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::AsymmetricSignResponse>
  AsymmetricSign(google::cloud::kms::v1::AsymmetricSignRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::AsymmetricDecryptResponse>
  AsymmetricDecrypt(
      google::cloud::kms::v1::AsymmetricDecryptRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::MacSignResponse> MacSign(
      google::cloud::kms::v1::MacSignRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::MacVerifyResponse> MacVerify(
      google::cloud::kms::v1::MacVerifyRequest const& request);

  virtual StatusOr<google::cloud::kms::v1::GenerateRandomBytesResponse>
  GenerateRandomBytes(
      google::cloud::kms::v1::GenerateRandomBytesRequest const& request);
};

/**
 * A factory function to construct an object of type
 * `KeyManagementServiceConnection`.
 *
 * The returned connection object should not be used directly; instead it
 * should be passed as an argument to the constructor of
 * KeyManagementServiceClient, and that class used instead.
 *
 * The optional @p opts argument may be used to configure aspects of the
 * returned `KeyManagementServiceConnection`. Expected options are any of the
 * types in the following option lists:
 *
 * - `google::cloud::CommonOptionList`
 * - `google::cloud::GrpcOptionList`
 * - `google::cloud::kms::KeyManagementServicePolicyOptionList`
 *
 * @note Unrecognized options will be ignored. To debug issues with options set
 *     `GOOGLE_CLOUD_CPP_ENABLE_CLOG=yes` in the environment and unexpected
 *     options will be logged.
 *
 * @param options (optional) Configure the `KeyManagementServiceConnection`
 * created by this function.
 */
std::shared_ptr<KeyManagementServiceConnection>
MakeKeyManagementServiceConnection(Options options = {});

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace kms
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace kms_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<kms::KeyManagementServiceConnection>
MakeKeyManagementServiceConnection(
    std::shared_ptr<KeyManagementServiceStub> stub, Options options);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace kms_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_KMS_KEY_MANAGEMENT_CONNECTION_H
