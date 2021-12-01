// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef QUERYOBJECT_H
#define QUERYOBJECT_H

#include "TodaySchema.h"

namespace graphql::today::object {

namespace QueryStubs {

template <class TImpl>
concept HasNode = requires (TImpl impl, service::FieldParams params, response::IdType idArg) 
{
	{ service::FieldResult<std::shared_ptr<service::Object>> { impl.getNode(std::move(params), std::move(idArg)) } };
};

template <class TImpl>
concept HasAppointments = requires (TImpl impl, service::FieldParams params, std::optional<response::IntType> firstArg, std::optional<response::Value> afterArg, std::optional<response::IntType> lastArg, std::optional<response::Value> beforeArg) 
{
	{ service::FieldResult<std::shared_ptr<AppointmentConnection>> { impl.getAppointments(std::move(params), std::move(firstArg), std::move(afterArg), std::move(lastArg), std::move(beforeArg)) } };
};

template <class TImpl>
concept HasTasks = requires (TImpl impl, service::FieldParams params, std::optional<response::IntType> firstArg, std::optional<response::Value> afterArg, std::optional<response::IntType> lastArg, std::optional<response::Value> beforeArg) 
{
	{ service::FieldResult<std::shared_ptr<TaskConnection>> { impl.getTasks(std::move(params), std::move(firstArg), std::move(afterArg), std::move(lastArg), std::move(beforeArg)) } };
};

template <class TImpl>
concept HasUnreadCounts = requires (TImpl impl, service::FieldParams params, std::optional<response::IntType> firstArg, std::optional<response::Value> afterArg, std::optional<response::IntType> lastArg, std::optional<response::Value> beforeArg) 
{
	{ service::FieldResult<std::shared_ptr<FolderConnection>> { impl.getUnreadCounts(std::move(params), std::move(firstArg), std::move(afterArg), std::move(lastArg), std::move(beforeArg)) } };
};

template <class TImpl>
concept HasAppointmentsById = requires (TImpl impl, service::FieldParams params, std::vector<response::IdType> idsArg) 
{
	{ service::FieldResult<std::vector<std::shared_ptr<Appointment>>> { impl.getAppointmentsById(std::move(params), std::move(idsArg)) } };
};

template <class TImpl>
concept HasTasksById = requires (TImpl impl, service::FieldParams params, std::vector<response::IdType> idsArg) 
{
	{ service::FieldResult<std::vector<std::shared_ptr<Task>>> { impl.getTasksById(std::move(params), std::move(idsArg)) } };
};

template <class TImpl>
concept HasUnreadCountsById = requires (TImpl impl, service::FieldParams params, std::vector<response::IdType> idsArg) 
{
	{ service::FieldResult<std::vector<std::shared_ptr<Folder>>> { impl.getUnreadCountsById(std::move(params), std::move(idsArg)) } };
};

template <class TImpl>
concept HasNested = requires (TImpl impl, service::FieldParams params) 
{
	{ service::FieldResult<std::shared_ptr<NestedType>> { impl.getNested(std::move(params)) } };
};

template <class TImpl>
concept HasUnimplemented = requires (TImpl impl, service::FieldParams params) 
{
	{ service::FieldResult<response::StringType> { impl.getUnimplemented(std::move(params)) } };
};

template <class TImpl>
concept HasExpensive = requires (TImpl impl, service::FieldParams params) 
{
	{ service::FieldResult<std::vector<std::shared_ptr<Expensive>>> { impl.getExpensive(std::move(params)) } };
};

template <class TImpl>
concept HasTestTaskState = requires (TImpl impl, service::FieldParams params) 
{
	{ service::FieldResult<TaskState> { impl.getTestTaskState(std::move(params)) } };
};

template <class TImpl>
concept HasAnyType = requires (TImpl impl, service::FieldParams params, std::vector<response::IdType> idsArg) 
{
	{ service::FieldResult<std::vector<std::shared_ptr<service::Object>>> { impl.getAnyType(std::move(params), std::move(idsArg)) } };
};

} // namespace QueryStubs

class Query
	: public service::Object
{
private:
	service::AwaitableResolver resolveNode(service::ResolverParams&& params);
	service::AwaitableResolver resolveAppointments(service::ResolverParams&& params);
	service::AwaitableResolver resolveTasks(service::ResolverParams&& params);
	service::AwaitableResolver resolveUnreadCounts(service::ResolverParams&& params);
	service::AwaitableResolver resolveAppointmentsById(service::ResolverParams&& params);
	service::AwaitableResolver resolveTasksById(service::ResolverParams&& params);
	service::AwaitableResolver resolveUnreadCountsById(service::ResolverParams&& params);
	service::AwaitableResolver resolveNested(service::ResolverParams&& params);
	service::AwaitableResolver resolveUnimplemented(service::ResolverParams&& params);
	service::AwaitableResolver resolveExpensive(service::ResolverParams&& params);
	service::AwaitableResolver resolveTestTaskState(service::ResolverParams&& params);
	service::AwaitableResolver resolveAnyType(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);
	service::AwaitableResolver resolve_schema(service::ResolverParams&& params);
	service::AwaitableResolver resolve_type(service::ResolverParams&& params);

	std::shared_ptr<schema::Schema> _schema;

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::shared_ptr<service::Object>> getNode(service::FieldParams&& params, response::IdType&& idArg) const = 0;
		virtual service::FieldResult<std::shared_ptr<AppointmentConnection>> getAppointments(service::FieldParams&& params, std::optional<response::IntType>&& firstArg, std::optional<response::Value>&& afterArg, std::optional<response::IntType>&& lastArg, std::optional<response::Value>&& beforeArg) const = 0;
		virtual service::FieldResult<std::shared_ptr<TaskConnection>> getTasks(service::FieldParams&& params, std::optional<response::IntType>&& firstArg, std::optional<response::Value>&& afterArg, std::optional<response::IntType>&& lastArg, std::optional<response::Value>&& beforeArg) const = 0;
		virtual service::FieldResult<std::shared_ptr<FolderConnection>> getUnreadCounts(service::FieldParams&& params, std::optional<response::IntType>&& firstArg, std::optional<response::Value>&& afterArg, std::optional<response::IntType>&& lastArg, std::optional<response::Value>&& beforeArg) const = 0;
		virtual service::FieldResult<std::vector<std::shared_ptr<Appointment>>> getAppointmentsById(service::FieldParams&& params, std::vector<response::IdType>&& idsArg) const = 0;
		virtual service::FieldResult<std::vector<std::shared_ptr<Task>>> getTasksById(service::FieldParams&& params, std::vector<response::IdType>&& idsArg) const = 0;
		virtual service::FieldResult<std::vector<std::shared_ptr<Folder>>> getUnreadCountsById(service::FieldParams&& params, std::vector<response::IdType>&& idsArg) const = 0;
		virtual service::FieldResult<std::shared_ptr<NestedType>> getNested(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<response::StringType> getUnimplemented(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<std::vector<std::shared_ptr<Expensive>>> getExpensive(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<TaskState> getTestTaskState(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<std::vector<std::shared_ptr<service::Object>>> getAnyType(service::FieldParams&& params, std::vector<response::IdType>&& idsArg) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<std::shared_ptr<service::Object>> getNode(service::FieldParams&& params, response::IdType&& idArg) const final
		{
			if constexpr (QueryStubs::HasNode<T>)
			{
				return { _pimpl->getNode(std::move(params), std::move(idArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Query::getNode is not implemented)ex");
			}
		}

		service::FieldResult<std::shared_ptr<AppointmentConnection>> getAppointments(service::FieldParams&& params, std::optional<response::IntType>&& firstArg, std::optional<response::Value>&& afterArg, std::optional<response::IntType>&& lastArg, std::optional<response::Value>&& beforeArg) const final
		{
			if constexpr (QueryStubs::HasAppointments<T>)
			{
				return { _pimpl->getAppointments(std::move(params), std::move(firstArg), std::move(afterArg), std::move(lastArg), std::move(beforeArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Query::getAppointments is not implemented)ex");
			}
		}

		service::FieldResult<std::shared_ptr<TaskConnection>> getTasks(service::FieldParams&& params, std::optional<response::IntType>&& firstArg, std::optional<response::Value>&& afterArg, std::optional<response::IntType>&& lastArg, std::optional<response::Value>&& beforeArg) const final
		{
			if constexpr (QueryStubs::HasTasks<T>)
			{
				return { _pimpl->getTasks(std::move(params), std::move(firstArg), std::move(afterArg), std::move(lastArg), std::move(beforeArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Query::getTasks is not implemented)ex");
			}
		}

		service::FieldResult<std::shared_ptr<FolderConnection>> getUnreadCounts(service::FieldParams&& params, std::optional<response::IntType>&& firstArg, std::optional<response::Value>&& afterArg, std::optional<response::IntType>&& lastArg, std::optional<response::Value>&& beforeArg) const final
		{
			if constexpr (QueryStubs::HasUnreadCounts<T>)
			{
				return { _pimpl->getUnreadCounts(std::move(params), std::move(firstArg), std::move(afterArg), std::move(lastArg), std::move(beforeArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Query::getUnreadCounts is not implemented)ex");
			}
		}

		service::FieldResult<std::vector<std::shared_ptr<Appointment>>> getAppointmentsById(service::FieldParams&& params, std::vector<response::IdType>&& idsArg) const final
		{
			if constexpr (QueryStubs::HasAppointmentsById<T>)
			{
				return { _pimpl->getAppointmentsById(std::move(params), std::move(idsArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Query::getAppointmentsById is not implemented)ex");
			}
		}

		service::FieldResult<std::vector<std::shared_ptr<Task>>> getTasksById(service::FieldParams&& params, std::vector<response::IdType>&& idsArg) const final
		{
			if constexpr (QueryStubs::HasTasksById<T>)
			{
				return { _pimpl->getTasksById(std::move(params), std::move(idsArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Query::getTasksById is not implemented)ex");
			}
		}

		service::FieldResult<std::vector<std::shared_ptr<Folder>>> getUnreadCountsById(service::FieldParams&& params, std::vector<response::IdType>&& idsArg) const final
		{
			if constexpr (QueryStubs::HasUnreadCountsById<T>)
			{
				return { _pimpl->getUnreadCountsById(std::move(params), std::move(idsArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Query::getUnreadCountsById is not implemented)ex");
			}
		}

		service::FieldResult<std::shared_ptr<NestedType>> getNested(service::FieldParams&& params) const final
		{
			if constexpr (QueryStubs::HasNested<T>)
			{
				return { _pimpl->getNested(std::move(params)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Query::getNested is not implemented)ex");
			}
		}

		service::FieldResult<response::StringType> getUnimplemented(service::FieldParams&& params) const final
		{
			if constexpr (QueryStubs::HasUnimplemented<T>)
			{
				return { _pimpl->getUnimplemented(std::move(params)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Query::getUnimplemented is not implemented)ex");
			}
		}

		service::FieldResult<std::vector<std::shared_ptr<Expensive>>> getExpensive(service::FieldParams&& params) const final
		{
			if constexpr (QueryStubs::HasExpensive<T>)
			{
				return { _pimpl->getExpensive(std::move(params)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Query::getExpensive is not implemented)ex");
			}
		}

		service::FieldResult<TaskState> getTestTaskState(service::FieldParams&& params) const final
		{
			if constexpr (QueryStubs::HasTestTaskState<T>)
			{
				return { _pimpl->getTestTaskState(std::move(params)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Query::getTestTaskState is not implemented)ex");
			}
		}

		service::FieldResult<std::vector<std::shared_ptr<service::Object>>> getAnyType(service::FieldParams&& params, std::vector<response::IdType>&& idsArg) const final
		{
			if constexpr (QueryStubs::HasAnyType<T>)
			{
				return { _pimpl->getAnyType(std::move(params), std::move(idsArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Query::getAnyType is not implemented)ex");
			}
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Query(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	Query(std::shared_ptr<T> pimpl)
		: Query { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}
};

} // namespace graphql::today::object

#endif // QUERYOBJECT_H
