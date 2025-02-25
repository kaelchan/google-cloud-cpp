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
// source: google/cloud/batch/v1/batch.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BATCH_V1_BATCH_CLIENT_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BATCH_V1_BATCH_CLIENT_H

#include "google/cloud/batch/v1/batch_connection.h"
#include "google/cloud/future.h"
#include "google/cloud/options.h"
#include "google/cloud/polling_policy.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <google/longrunning/operations.grpc.pb.h>
#include <map>
#include <memory>
#include <string>

namespace google {
namespace cloud {
namespace batch_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

///
/// Google Batch Service.
/// The service manages user submitted batch jobs and allocates Google Compute
/// Engine VM instances to run the jobs.
///
/// @par Equality
///
/// Instances of this class created via copy-construction or copy-assignment
/// always compare equal. Instances created with equal
/// `std::shared_ptr<*Connection>` objects compare equal. Objects that compare
/// equal share the same underlying resources.
///
/// @par Performance
///
/// Creating a new instance of this class is a relatively expensive operation,
/// new objects establish new connections to the service. In contrast,
/// copy-construction, move-construction, and the corresponding assignment
/// operations are relatively efficient as the copies share all underlying
/// resources.
///
/// @par Thread Safety
///
/// Concurrent access to different instances of this class, even if they compare
/// equal, is guaranteed to work. Two or more threads operating on the same
/// instance of this class is not guaranteed to work. Since copy-construction
/// and move-construction is a relatively efficient operation, consider using
/// such a copy when using this class from multiple threads.
///
class BatchServiceClient {
 public:
  explicit BatchServiceClient(
      std::shared_ptr<BatchServiceConnection> connection, Options opts = {});
  ~BatchServiceClient();

  ///@{
  /// @name Copy and move support
  BatchServiceClient(BatchServiceClient const&) = default;
  BatchServiceClient& operator=(BatchServiceClient const&) = default;
  BatchServiceClient(BatchServiceClient&&) = default;
  BatchServiceClient& operator=(BatchServiceClient&&) = default;
  ///@}

  ///@{
  /// @name Equality
  friend bool operator==(BatchServiceClient const& a,
                         BatchServiceClient const& b) {
    return a.connection_ == b.connection_;
  }
  friend bool operator!=(BatchServiceClient const& a,
                         BatchServiceClient const& b) {
    return !(a == b);
  }
  ///@}

  // clang-format off
  ///
  /// Create a Job.
  ///
  /// @param parent  Required. The parent resource name where the Job will be created.
  ///  Pattern: "projects/{project}/locations/{location}"
  /// @param job  Required. The Job to create.
  /// @param job_id  ID used to uniquely identify the Job within its parent scope.
  ///  This field should contain at most 63 characters and must start with
  ///  lowercase characters.
  ///  Only lowercase characters, numbers and '-' are accepted.
  ///  The '-' character cannot be the first or the last one.
  ///  A system generated ID will be used if the field is not set.
  ///  @n
  ///  The job.name field in the request will be ignored and the created resource
  ///  name of the Job will be "{parent}/jobs/{job_id}".
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.batch.v1.Job])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.batch.v1.CreateJobRequest]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L102}
  /// [google.cloud.batch.v1.Job]: @googleapis_reference_link{google/cloud/batch/v1/job.proto#L35}
  ///
  // clang-format on
  StatusOr<google::cloud::batch::v1::Job> CreateJob(
      std::string const& parent, google::cloud::batch::v1::Job const& job,
      std::string const& job_id, Options opts = {});

  // clang-format off
  ///
  /// Create a Job.
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.cloud.batch.v1.CreateJobRequest].
  ///     Proto messages are converted to C++ classes by Protobuf, using the
  ///     [Protobuf mapping rules].
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.batch.v1.Job])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.batch.v1.CreateJobRequest]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L102}
  /// [google.cloud.batch.v1.Job]: @googleapis_reference_link{google/cloud/batch/v1/job.proto#L35}
  ///
  // clang-format on
  StatusOr<google::cloud::batch::v1::Job> CreateJob(
      google::cloud::batch::v1::CreateJobRequest const& request,
      Options opts = {});

  // clang-format off
  ///
  /// Get a Job specified by its resource name.
  ///
  /// @param name  Required. Job name.
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.batch.v1.Job])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.batch.v1.GetJobRequest]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L141}
  /// [google.cloud.batch.v1.Job]: @googleapis_reference_link{google/cloud/batch/v1/job.proto#L35}
  ///
  // clang-format on
  StatusOr<google::cloud::batch::v1::Job> GetJob(std::string const& name,
                                                 Options opts = {});

  // clang-format off
  ///
  /// Get a Job specified by its resource name.
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.cloud.batch.v1.GetJobRequest].
  ///     Proto messages are converted to C++ classes by Protobuf, using the
  ///     [Protobuf mapping rules].
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.batch.v1.Job])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.batch.v1.GetJobRequest]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L141}
  /// [google.cloud.batch.v1.Job]: @googleapis_reference_link{google/cloud/batch/v1/job.proto#L35}
  ///
  // clang-format on
  StatusOr<google::cloud::batch::v1::Job> GetJob(
      google::cloud::batch::v1::GetJobRequest const& request,
      Options opts = {});

  // clang-format off
  ///
  /// Delete a Job.
  ///
  /// @param name  Job name.
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return A [`future`] that becomes satisfied when the LRO
  ///     ([Long Running Operation]) completes or the polling policy in effect
  ///     for this call is exhausted. The future is satisfied with an error if
  ///     the LRO completes with an error or the polling policy is exhausted.
  ///     In this case the [`StatusOr`] returned by the future contains the
  ///     error. If the LRO completes successfully the value of the future
  ///     contains the LRO's result. For this RPC the result is a
  ///     [google.cloud.batch.v1.OperationMetadata] proto message.
  ///     The C++ class representing this message is created by Protobuf, using
  ///     the [Protobuf mapping rules].
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [Long Running Operation]: https://google.aip.dev/151
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.batch.v1.DeleteJobRequest]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L150}
  /// [google.cloud.batch.v1.OperationMetadata]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L248}
  ///
  // clang-format on
  future<StatusOr<google::cloud::batch::v1::OperationMetadata>> DeleteJob(
      std::string const& name, Options opts = {});

  // clang-format off
  ///
  /// Delete a Job.
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.cloud.batch.v1.DeleteJobRequest].
  ///     Proto messages are converted to C++ classes by Protobuf, using the
  ///     [Protobuf mapping rules].
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return A [`future`] that becomes satisfied when the LRO
  ///     ([Long Running Operation]) completes or the polling policy in effect
  ///     for this call is exhausted. The future is satisfied with an error if
  ///     the LRO completes with an error or the polling policy is exhausted.
  ///     In this case the [`StatusOr`] returned by the future contains the
  ///     error. If the LRO completes successfully the value of the future
  ///     contains the LRO's result. For this RPC the result is a
  ///     [google.cloud.batch.v1.OperationMetadata] proto message.
  ///     The C++ class representing this message is created by Protobuf, using
  ///     the [Protobuf mapping rules].
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [Long Running Operation]: https://google.aip.dev/151
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.batch.v1.DeleteJobRequest]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L150}
  /// [google.cloud.batch.v1.OperationMetadata]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L248}
  ///
  // clang-format on
  future<StatusOr<google::cloud::batch::v1::OperationMetadata>> DeleteJob(
      google::cloud::batch::v1::DeleteJobRequest const& request,
      Options opts = {});

  // clang-format off
  ///
  /// List all Jobs for a project within a region.
  ///
  /// @param parent  Parent path.
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return a [StreamRange](@ref google::cloud::StreamRange)
  ///     to iterate of the results. See the documentation of this type for
  ///     details. In brief, this class has `begin()` and `end()` member
  ///     functions returning a iterator class meeting the
  ///     [input iterator requirements]. The value type for this iterator is a
  ///     [`StatusOr`] as the iteration may fail even after some values are
  ///     retrieved successfully, for example, if there is a network disconnect.
  ///     An empty set of results does not indicate an error, it indicates
  ///     that there are no resources meeting the request criteria.
  ///     On a successful iteration the `StatusOr<T>` contains elements of type
  ///     [google.cloud.batch.v1.Job], or rather,
  ///     the C++ class generated by Protobuf from that type. Please consult the
  ///     Protobuf documentation for details on the [Protobuf mapping rules].
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.batch.v1.Job]: @googleapis_reference_link{google/cloud/batch/v1/job.proto#L35}
  /// [google.cloud.batch.v1.ListJobsRequest]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L174}
  ///
  // clang-format on
  StreamRange<google::cloud::batch::v1::Job> ListJobs(std::string const& parent,
                                                      Options opts = {});

  // clang-format off
  ///
  /// List all Jobs for a project within a region.
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.cloud.batch.v1.ListJobsRequest].
  ///     Proto messages are converted to C++ classes by Protobuf, using the
  ///     [Protobuf mapping rules].
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return a [StreamRange](@ref google::cloud::StreamRange)
  ///     to iterate of the results. See the documentation of this type for
  ///     details. In brief, this class has `begin()` and `end()` member
  ///     functions returning a iterator class meeting the
  ///     [input iterator requirements]. The value type for this iterator is a
  ///     [`StatusOr`] as the iteration may fail even after some values are
  ///     retrieved successfully, for example, if there is a network disconnect.
  ///     An empty set of results does not indicate an error, it indicates
  ///     that there are no resources meeting the request criteria.
  ///     On a successful iteration the `StatusOr<T>` contains elements of type
  ///     [google.cloud.batch.v1.Job], or rather,
  ///     the C++ class generated by Protobuf from that type. Please consult the
  ///     Protobuf documentation for details on the [Protobuf mapping rules].
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.batch.v1.Job]: @googleapis_reference_link{google/cloud/batch/v1/job.proto#L35}
  /// [google.cloud.batch.v1.ListJobsRequest]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L174}
  ///
  // clang-format on
  StreamRange<google::cloud::batch::v1::Job> ListJobs(
      google::cloud::batch::v1::ListJobsRequest request, Options opts = {});

  // clang-format off
  ///
  /// Return a single Task.
  ///
  /// @param name  Required. Task name.
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.batch.v1.Task])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.batch.v1.GetTaskRequest]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L239}
  /// [google.cloud.batch.v1.Task]: @googleapis_reference_link{google/cloud/batch/v1/task.proto#L401}
  ///
  // clang-format on
  StatusOr<google::cloud::batch::v1::Task> GetTask(std::string const& name,
                                                   Options opts = {});

  // clang-format off
  ///
  /// Return a single Task.
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.cloud.batch.v1.GetTaskRequest].
  ///     Proto messages are converted to C++ classes by Protobuf, using the
  ///     [Protobuf mapping rules].
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.batch.v1.Task])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.batch.v1.GetTaskRequest]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L239}
  /// [google.cloud.batch.v1.Task]: @googleapis_reference_link{google/cloud/batch/v1/task.proto#L401}
  ///
  // clang-format on
  StatusOr<google::cloud::batch::v1::Task> GetTask(
      google::cloud::batch::v1::GetTaskRequest const& request,
      Options opts = {});

  // clang-format off
  ///
  /// List Tasks associated with a job.
  ///
  /// @param parent  Required. Name of a TaskGroup from which Tasks are being requested.
  ///  Pattern:
  ///  "projects/{project}/locations/{location}/jobs/{job}/taskGroups/{task_group}"
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return a [StreamRange](@ref google::cloud::StreamRange)
  ///     to iterate of the results. See the documentation of this type for
  ///     details. In brief, this class has `begin()` and `end()` member
  ///     functions returning a iterator class meeting the
  ///     [input iterator requirements]. The value type for this iterator is a
  ///     [`StatusOr`] as the iteration may fail even after some values are
  ///     retrieved successfully, for example, if there is a network disconnect.
  ///     An empty set of results does not indicate an error, it indicates
  ///     that there are no resources meeting the request criteria.
  ///     On a successful iteration the `StatusOr<T>` contains elements of type
  ///     [google.cloud.batch.v1.Task], or rather,
  ///     the C++ class generated by Protobuf from that type. Please consult the
  ///     Protobuf documentation for details on the [Protobuf mapping rules].
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.batch.v1.ListTasksRequest]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L205}
  /// [google.cloud.batch.v1.Task]: @googleapis_reference_link{google/cloud/batch/v1/task.proto#L401}
  ///
  // clang-format on
  StreamRange<google::cloud::batch::v1::Task> ListTasks(
      std::string const& parent, Options opts = {});

  // clang-format off
  ///
  /// List Tasks associated with a job.
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.cloud.batch.v1.ListTasksRequest].
  ///     Proto messages are converted to C++ classes by Protobuf, using the
  ///     [Protobuf mapping rules].
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return a [StreamRange](@ref google::cloud::StreamRange)
  ///     to iterate of the results. See the documentation of this type for
  ///     details. In brief, this class has `begin()` and `end()` member
  ///     functions returning a iterator class meeting the
  ///     [input iterator requirements]. The value type for this iterator is a
  ///     [`StatusOr`] as the iteration may fail even after some values are
  ///     retrieved successfully, for example, if there is a network disconnect.
  ///     An empty set of results does not indicate an error, it indicates
  ///     that there are no resources meeting the request criteria.
  ///     On a successful iteration the `StatusOr<T>` contains elements of type
  ///     [google.cloud.batch.v1.Task], or rather,
  ///     the C++ class generated by Protobuf from that type. Please consult the
  ///     Protobuf documentation for details on the [Protobuf mapping rules].
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.batch.v1.ListTasksRequest]: @googleapis_reference_link{google/cloud/batch/v1/batch.proto#L205}
  /// [google.cloud.batch.v1.Task]: @googleapis_reference_link{google/cloud/batch/v1/task.proto#L401}
  ///
  // clang-format on
  StreamRange<google::cloud::batch::v1::Task> ListTasks(
      google::cloud::batch::v1::ListTasksRequest request, Options opts = {});

 private:
  std::shared_ptr<BatchServiceConnection> connection_;
  Options options_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace batch_v1
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BATCH_V1_BATCH_CLIENT_H
