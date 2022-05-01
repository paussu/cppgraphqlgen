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

// Check if the library version is compatible with clientgen 4.2.0
static_assert(graphql::internal::MajorVersion == 4, "regenerate with clientgen: major version mismatch");
static_assert(graphql::internal::MinorVersion == 2, "regenerate with clientgen: minor version mismatch");

#include <optional>
#include <string>
#include <vector>

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
namespace graphql::client::subscription::TestSubscription {

// Return the original text of the request document.
const std::string& GetRequestText() noexcept;

// Return a pre-parsed, pre-validated request object.
const peg::ast& GetRequestObject() noexcept;

struct Response
{
	struct nextAppointment_Appointment
	{
		response::IdType nextAppointmentId {};
		std::optional<response::Value> when {};
		std::optional<std::string> subject {};
		bool isNow {};
	};

	std::optional<nextAppointment_Appointment> nextAppointment {};
};

Response parseResponse(response::Value&& response);

} // namespace graphql::client::subscription::TestSubscription

#endif // SUBSCRIBECLIENT_H
