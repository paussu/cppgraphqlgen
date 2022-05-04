// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "QueryClient.h"

#include <algorithm>
#include <array>
#include <sstream>
#include <stdexcept>
#include <string_view>

using namespace std::literals;

namespace graphql::client {
namespace query {

const std::string& GetRequestText() noexcept
{
	static const auto s_request = R"gql(
		# Copyright (c) Microsoft Corporation. All rights reserved.
		# Licensed under the MIT License.
		
		query {
		  appointments {
		    edges {
		      node {
		        id
		        subject
		        when
		        isNow
		        __typename
		      }
		    }
		  }
		  tasks {
		    edges {
		      node {
		        id
		        title
		        isComplete
		        __typename
		      }
		    }
		  }
		  unreadCounts {
		    edges {
		      node {
		        id
		        name
		        unreadCount
		        __typename
		      }
		    }
		  }
		
		  # Read a field with an enum type
		  testTaskState
		
		  # Try a field with a union type
		  anyType(ids: ["ZmFrZVRhc2tJZA=="]) {
		    __typename
		    ...on Node {
		      id
		    }
		    ...on Task {
		      id
		      title
		      isComplete
		    }
		    ...on Appointment {
		      id
		      subject
		      when
		      isNow
		    }
		  }
		
		  # Try a field with a C++ keyword
		  default
		}
	)gql"s;

	return s_request;
}

const peg::ast& GetRequestObject() noexcept
{
	static const auto s_request = []() noexcept {
		auto ast = peg::parseString(GetRequestText());

		// This has already been validated against the schema by clientgen.
		ast.validated = true;

		return ast;
	}();

	return s_request;
}

} // namespace query

static const std::array<std::string_view, 4> s_namesTaskState = {
	"New"sv,
	"Started"sv,
	"Complete"sv,
	"Unassigned"sv,
};

template <>
query::Query::TaskState ModifiedResponse<query::Query::TaskState>::parse(response::Value&& value)
{
	if (!value.maybe_enum())
	{
		throw std::logic_error { "not a valid TaskState value" };
	}

	const auto itr = std::find(s_namesTaskState.cbegin(), s_namesTaskState.cend(), value.release<std::string>());

	if (itr == s_namesTaskState.cend())
	{
		throw std::logic_error { "not a valid TaskState value" };
	}

	return static_cast<query::Query::TaskState>(itr - s_namesTaskState.cbegin());
}

template <>
query::Query::Response::appointments_AppointmentConnection::edges_AppointmentEdge::node_Appointment ModifiedResponse<query::Query::Response::appointments_AppointmentConnection::edges_AppointmentEdge::node_Appointment>::parse(response::Value&& response)
{
	query::Query::Response::appointments_AppointmentConnection::edges_AppointmentEdge::node_Appointment result;

	if (response.type() == response::Type::Map)
	{
		auto members = response.release<response::MapType>();

		for (auto& member : members)
		{
			if (member.first == R"js(id)js"sv)
			{
				result.id = ModifiedResponse<response::IdType>::parse(std::move(member.second));
				continue;
			}
			if (member.first == R"js(subject)js"sv)
			{
				result.subject = ModifiedResponse<std::string>::parse<TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
			if (member.first == R"js(when)js"sv)
			{
				result.when = ModifiedResponse<response::Value>::parse<TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
			if (member.first == R"js(isNow)js"sv)
			{
				result.isNow = ModifiedResponse<bool>::parse(std::move(member.second));
				continue;
			}
			if (member.first == R"js(__typename)js"sv)
			{
				result._typename = ModifiedResponse<std::string>::parse(std::move(member.second));
				continue;
			}
		}
	}

	return result;
}

template <>
query::Query::Response::appointments_AppointmentConnection::edges_AppointmentEdge ModifiedResponse<query::Query::Response::appointments_AppointmentConnection::edges_AppointmentEdge>::parse(response::Value&& response)
{
	query::Query::Response::appointments_AppointmentConnection::edges_AppointmentEdge result;

	if (response.type() == response::Type::Map)
	{
		auto members = response.release<response::MapType>();

		for (auto& member : members)
		{
			if (member.first == R"js(node)js"sv)
			{
				result.node = ModifiedResponse<query::Query::Response::appointments_AppointmentConnection::edges_AppointmentEdge::node_Appointment>::parse<TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
		}
	}

	return result;
}

template <>
query::Query::Response::appointments_AppointmentConnection ModifiedResponse<query::Query::Response::appointments_AppointmentConnection>::parse(response::Value&& response)
{
	query::Query::Response::appointments_AppointmentConnection result;

	if (response.type() == response::Type::Map)
	{
		auto members = response.release<response::MapType>();

		for (auto& member : members)
		{
			if (member.first == R"js(edges)js"sv)
			{
				result.edges = ModifiedResponse<query::Query::Response::appointments_AppointmentConnection::edges_AppointmentEdge>::parse<TypeModifier::Nullable, TypeModifier::List, TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
		}
	}

	return result;
}

template <>
query::Query::Response::tasks_TaskConnection::edges_TaskEdge::node_Task ModifiedResponse<query::Query::Response::tasks_TaskConnection::edges_TaskEdge::node_Task>::parse(response::Value&& response)
{
	query::Query::Response::tasks_TaskConnection::edges_TaskEdge::node_Task result;

	if (response.type() == response::Type::Map)
	{
		auto members = response.release<response::MapType>();

		for (auto& member : members)
		{
			if (member.first == R"js(id)js"sv)
			{
				result.id = ModifiedResponse<response::IdType>::parse(std::move(member.second));
				continue;
			}
			if (member.first == R"js(title)js"sv)
			{
				result.title = ModifiedResponse<std::string>::parse<TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
			if (member.first == R"js(isComplete)js"sv)
			{
				result.isComplete = ModifiedResponse<bool>::parse(std::move(member.second));
				continue;
			}
			if (member.first == R"js(__typename)js"sv)
			{
				result._typename = ModifiedResponse<std::string>::parse(std::move(member.second));
				continue;
			}
		}
	}

	return result;
}

template <>
query::Query::Response::tasks_TaskConnection::edges_TaskEdge ModifiedResponse<query::Query::Response::tasks_TaskConnection::edges_TaskEdge>::parse(response::Value&& response)
{
	query::Query::Response::tasks_TaskConnection::edges_TaskEdge result;

	if (response.type() == response::Type::Map)
	{
		auto members = response.release<response::MapType>();

		for (auto& member : members)
		{
			if (member.first == R"js(node)js"sv)
			{
				result.node = ModifiedResponse<query::Query::Response::tasks_TaskConnection::edges_TaskEdge::node_Task>::parse<TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
		}
	}

	return result;
}

template <>
query::Query::Response::tasks_TaskConnection ModifiedResponse<query::Query::Response::tasks_TaskConnection>::parse(response::Value&& response)
{
	query::Query::Response::tasks_TaskConnection result;

	if (response.type() == response::Type::Map)
	{
		auto members = response.release<response::MapType>();

		for (auto& member : members)
		{
			if (member.first == R"js(edges)js"sv)
			{
				result.edges = ModifiedResponse<query::Query::Response::tasks_TaskConnection::edges_TaskEdge>::parse<TypeModifier::Nullable, TypeModifier::List, TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
		}
	}

	return result;
}

template <>
query::Query::Response::unreadCounts_FolderConnection::edges_FolderEdge::node_Folder ModifiedResponse<query::Query::Response::unreadCounts_FolderConnection::edges_FolderEdge::node_Folder>::parse(response::Value&& response)
{
	query::Query::Response::unreadCounts_FolderConnection::edges_FolderEdge::node_Folder result;

	if (response.type() == response::Type::Map)
	{
		auto members = response.release<response::MapType>();

		for (auto& member : members)
		{
			if (member.first == R"js(id)js"sv)
			{
				result.id = ModifiedResponse<response::IdType>::parse(std::move(member.second));
				continue;
			}
			if (member.first == R"js(name)js"sv)
			{
				result.name = ModifiedResponse<std::string>::parse<TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
			if (member.first == R"js(unreadCount)js"sv)
			{
				result.unreadCount = ModifiedResponse<int>::parse(std::move(member.second));
				continue;
			}
			if (member.first == R"js(__typename)js"sv)
			{
				result._typename = ModifiedResponse<std::string>::parse(std::move(member.second));
				continue;
			}
		}
	}

	return result;
}

template <>
query::Query::Response::unreadCounts_FolderConnection::edges_FolderEdge ModifiedResponse<query::Query::Response::unreadCounts_FolderConnection::edges_FolderEdge>::parse(response::Value&& response)
{
	query::Query::Response::unreadCounts_FolderConnection::edges_FolderEdge result;

	if (response.type() == response::Type::Map)
	{
		auto members = response.release<response::MapType>();

		for (auto& member : members)
		{
			if (member.first == R"js(node)js"sv)
			{
				result.node = ModifiedResponse<query::Query::Response::unreadCounts_FolderConnection::edges_FolderEdge::node_Folder>::parse<TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
		}
	}

	return result;
}

template <>
query::Query::Response::unreadCounts_FolderConnection ModifiedResponse<query::Query::Response::unreadCounts_FolderConnection>::parse(response::Value&& response)
{
	query::Query::Response::unreadCounts_FolderConnection result;

	if (response.type() == response::Type::Map)
	{
		auto members = response.release<response::MapType>();

		for (auto& member : members)
		{
			if (member.first == R"js(edges)js"sv)
			{
				result.edges = ModifiedResponse<query::Query::Response::unreadCounts_FolderConnection::edges_FolderEdge>::parse<TypeModifier::Nullable, TypeModifier::List, TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
		}
	}

	return result;
}

template <>
query::Query::Response::anyType_UnionType ModifiedResponse<query::Query::Response::anyType_UnionType>::parse(response::Value&& response)
{
	query::Query::Response::anyType_UnionType result;

	if (response.type() == response::Type::Map)
	{
		auto members = response.release<response::MapType>();

		for (auto& member : members)
		{
			if (member.first == R"js(__typename)js"sv)
			{
				result._typename = ModifiedResponse<std::string>::parse(std::move(member.second));
				continue;
			}
			if (member.first == R"js(id)js"sv)
			{
				result.id = ModifiedResponse<response::IdType>::parse(std::move(member.second));
				continue;
			}
			if (member.first == R"js(title)js"sv)
			{
				result.title = ModifiedResponse<std::string>::parse<TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
			if (member.first == R"js(isComplete)js"sv)
			{
				result.isComplete = ModifiedResponse<bool>::parse(std::move(member.second));
				continue;
			}
			if (member.first == R"js(subject)js"sv)
			{
				result.subject = ModifiedResponse<std::string>::parse<TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
			if (member.first == R"js(when)js"sv)
			{
				result.when = ModifiedResponse<response::Value>::parse<TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
			if (member.first == R"js(isNow)js"sv)
			{
				result.isNow = ModifiedResponse<bool>::parse(std::move(member.second));
				continue;
			}
		}
	}

	return result;
}

namespace query::Query {

const std::string& GetOperationName() noexcept
{
	static const auto s_name = R"gql()gql"s;

	return s_name;
}

Response parseResponse(response::Value&& response)
{
	Response result;

	if (response.type() == response::Type::Map)
	{
		auto members = response.release<response::MapType>();

		for (auto& member : members)
		{
			if (member.first == R"js(appointments)js"sv)
			{
				result.appointments = ModifiedResponse<query::Query::Response::appointments_AppointmentConnection>::parse(std::move(member.second));
				continue;
			}
			if (member.first == R"js(tasks)js"sv)
			{
				result.tasks = ModifiedResponse<query::Query::Response::tasks_TaskConnection>::parse(std::move(member.second));
				continue;
			}
			if (member.first == R"js(unreadCounts)js"sv)
			{
				result.unreadCounts = ModifiedResponse<query::Query::Response::unreadCounts_FolderConnection>::parse(std::move(member.second));
				continue;
			}
			if (member.first == R"js(testTaskState)js"sv)
			{
				result.testTaskState = ModifiedResponse<TaskState>::parse(std::move(member.second));
				continue;
			}
			if (member.first == R"js(anyType)js"sv)
			{
				result.anyType = ModifiedResponse<query::Query::Response::anyType_UnionType>::parse<TypeModifier::List, TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
			if (member.first == R"js(default)js"sv)
			{
				result.default_ = ModifiedResponse<std::string>::parse<TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
		}
	}

	return result;
}

} // namespace query::Query
} // namespace graphql::client
