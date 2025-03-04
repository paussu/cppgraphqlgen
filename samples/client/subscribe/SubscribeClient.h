// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef SUBSCRIBECLIENT_H
#define SUBSCRIBECLIENT_H

#include "graphqlservice/GraphQLClient.h"
#include "graphqlservice/GraphQLParse.h"
#include "graphqlservice/GraphQLResponse.h"

#include "graphqlservice/internal/Version.h"

// Check if the library version is compatible with clientgen 4.5.0
static_assert(graphql::internal::MajorVersion == 4, "regenerate with clientgen: major version mismatch");
static_assert(graphql::internal::MinorVersion == 5, "regenerate with clientgen: minor version mismatch");

#include <optional>
#include <string>
#include <vector>

namespace graphql::client {

/// <summary>
/// Operation: subscription TestSubscription
/// </summary>
/// <code class="language-graphql">
/// # Copyright (c) Microsoft Corporation. All rights reserved.
/// # Licensed under the MIT License.
/// 
/// subscription TestSubscription {
///   nextAppointment: nextAppointmentChange {
///     nextAppointmentId: id
///     when
///     subject
///     isNow
///   }
/// }
/// </code>
namespace subscribe {

// Return the original text of the request document.
[[nodiscard]] const std::string& GetRequestText() noexcept;

// Return a pre-parsed, pre-validated request object.
[[nodiscard]] const peg::ast& GetRequestObject() noexcept;

} // namespace subscribe

namespace subscription::TestSubscription {

using subscribe::GetRequestText;
using subscribe::GetRequestObject;

// Return the name of this operation in the shared request document.
[[nodiscard]] const std::string& GetOperationName() noexcept;

struct [[nodiscard]] Response
{
	struct [[nodiscard]] nextAppointment_Appointment
	{
		response::IdType nextAppointmentId {};
		std::optional<response::Value> when {};
		std::optional<std::string> subject {};
		bool isNow {};
	};

	std::optional<nextAppointment_Appointment> nextAppointment {};
};

[[nodiscard]] Response parseResponse(response::Value&& response);

} // namespace subscription::TestSubscription
} // namespace graphql::client

#endif // SUBSCRIBECLIENT_H
