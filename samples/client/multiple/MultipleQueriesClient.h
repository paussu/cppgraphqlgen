// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef MULTIPLEQUERIESCLIENT_H
#define MULTIPLEQUERIESCLIENT_H

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

namespace graphql::client {

/// <summary>
/// Operations: query Appointments, query Tasks, query UnreadCounts, query Miscellaneous
/// </summary>
/// <code class="language-graphql">
/// # Copyright (c) Microsoft Corporation. All rights reserved.
/// # Licensed under the MIT License.
/// 
/// query Appointments {
///   appointments {
///     edges {
///       node {
///         id
///         subject
///         when
///         isNow
///         __typename
///       }
///     }
///   }
/// }
/// 
/// query Tasks {
///   tasks {
///     edges {
///       node {
///         id
///         title
///         isComplete
///         __typename
///       }
///     }
///   }
/// }
/// 
/// query UnreadCounts {
///   unreadCounts {
///     edges {
///       node {
///         id
///         name
///         unreadCount
///         __typename
///       }
///     }
///   }
/// }
/// 
/// query Miscellaneous {
///   # Read a field with an enum type
///   testTaskState
/// 
///   # Try a field with a union type
///   anyType(ids: ["ZmFrZVRhc2tJZA=="]) {
///     __typename
///     ...on Node {
///       id
///     }
///     ...on Task {
///       id
///       title
///       isComplete
///     }
///     ...on Appointment {
///       id
///       subject
///       when
///       isNow
///     }
///   }
/// 
///   # Try a field with a C++ keyword
///   default
/// }
/// </code>
namespace multiple {

// Return the original text of the request document.
const std::string& GetRequestText() noexcept;

// Return a pre-parsed, pre-validated request object.
const peg::ast& GetRequestObject() noexcept;

} // namespace multiple

namespace query::Appointments {

using multiple::GetRequestText;
using multiple::GetRequestObject;

// Return the name of this operation in the shared request document.
const std::string& GetOperationName() noexcept;

struct Response
{
	struct appointments_AppointmentConnection
	{
		struct edges_AppointmentEdge
		{
			struct node_Appointment
			{
				response::IdType id {};
				std::optional<std::string> subject {};
				std::optional<response::Value> when {};
				bool isNow {};
				std::string _typename {};
			};

			std::optional<node_Appointment> node {};
		};

		std::optional<std::vector<std::optional<edges_AppointmentEdge>>> edges {};
	};

	appointments_AppointmentConnection appointments {};
};

Response parseResponse(response::Value&& response);

} // namespace query::Appointments

namespace query::Tasks {

using multiple::GetRequestText;
using multiple::GetRequestObject;

// Return the name of this operation in the shared request document.
const std::string& GetOperationName() noexcept;

struct Response
{
	struct tasks_TaskConnection
	{
		struct edges_TaskEdge
		{
			struct node_Task
			{
				response::IdType id {};
				std::optional<std::string> title {};
				bool isComplete {};
				std::string _typename {};
			};

			std::optional<node_Task> node {};
		};

		std::optional<std::vector<std::optional<edges_TaskEdge>>> edges {};
	};

	tasks_TaskConnection tasks {};
};

Response parseResponse(response::Value&& response);

} // namespace query::Tasks

namespace query::UnreadCounts {

using multiple::GetRequestText;
using multiple::GetRequestObject;

// Return the name of this operation in the shared request document.
const std::string& GetOperationName() noexcept;

struct Response
{
	struct unreadCounts_FolderConnection
	{
		struct edges_FolderEdge
		{
			struct node_Folder
			{
				response::IdType id {};
				std::optional<std::string> name {};
				int unreadCount {};
				std::string _typename {};
			};

			std::optional<node_Folder> node {};
		};

		std::optional<std::vector<std::optional<edges_FolderEdge>>> edges {};
	};

	unreadCounts_FolderConnection unreadCounts {};
};

Response parseResponse(response::Value&& response);

} // namespace query::UnreadCounts

namespace query::Miscellaneous {

using multiple::GetRequestText;
using multiple::GetRequestObject;

// Return the name of this operation in the shared request document.
const std::string& GetOperationName() noexcept;

enum class [[nodiscard]] TaskState
{
	New,
	Started,
	Complete,
	Unassigned,
};

struct Response
{
	struct anyType_UnionType
	{
		std::string _typename {};
		response::IdType id {};
		std::optional<std::string> title {};
		bool isComplete {};
		std::optional<std::string> subject {};
		std::optional<response::Value> when {};
		bool isNow {};
	};

	TaskState testTaskState {};
	std::vector<std::optional<anyType_UnionType>> anyType {};
	std::optional<std::string> default_ {};
};

Response parseResponse(response::Value&& response);

} // namespace query::Miscellaneous
} // namespace graphql::client

#endif // MULTIPLEQUERIESCLIENT_H
