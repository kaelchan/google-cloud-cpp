// Copyright 2023 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_INTERNAL_REST_OPENTELEMETRY_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_INTERNAL_REST_OPENTELEMETRY_H

#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
#include "google/cloud/internal/rest_request.h"
#include <opentelemetry/nostd/shared_ptr.h>
#include <opentelemetry/trace/span.h>

namespace google {
namespace cloud {
namespace rest_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * Make a span, setting attributes related to HTTP.
 *
 * @see
 * https://opentelemetry.io/docs/reference/specification/trace/semantic_conventions/http/
 * for the semantic conventions used for span names and attributes.
 */
opentelemetry::nostd::shared_ptr<opentelemetry::trace::Span> MakeSpanHttp(
    RestRequest const& request, opentelemetry::nostd::string_view method);

opentelemetry::nostd::shared_ptr<opentelemetry::trace::Span>
MakeSpanHttpPayload(opentelemetry::trace::Span const& request_span);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace rest_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_INTERNAL_REST_OPENTELEMETRY_H
