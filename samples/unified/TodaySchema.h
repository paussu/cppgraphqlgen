// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef TODAYSCHEMA_H
#define TODAYSCHEMA_H

#include "graphqlservice/internal/Schema.h"

// Check if the library version is compatible with schemagen 4.0.0
static_assert(graphql::internal::MajorVersion == 4, "regenerate with schemagen: major version mismatch");
static_assert(graphql::internal::MinorVersion == 0, "regenerate with schemagen: minor version mismatch");

#include <memory>
#include <string>
#include <vector>

namespace graphql {
namespace today {

enum class TaskState
{
	New,
	Started,
	Complete,
	Unassigned
};

struct CompleteTaskInput
{
	response::IdType id;
	std::optional<TaskState> testTaskState;
	std::optional<response::BooleanType> isComplete;
	std::optional<response::StringType> clientMutationId;
};

struct ThirdNestedInput
{
	response::IdType id;
};

struct FourthNestedInput
{
	response::IdType id;
};

struct SecondNestedInput
{
	response::IdType id;
	ThirdNestedInput third;
};

struct FirstNestedInput
{
	response::IdType id;
	SecondNestedInput second;
	ThirdNestedInput third;
};

namespace object {

class Query;
class PageInfo;
class AppointmentEdge;
class AppointmentConnection;
class TaskEdge;
class TaskConnection;
class FolderEdge;
class FolderConnection;
class CompleteTaskPayload;
class Mutation;
class Subscription;
class Appointment;
class Task;
class Folder;
class NestedType;
class Expensive;

} // namespace object

struct Node
{
	virtual service::FieldResult<response::IdType> getId(service::FieldParams&& params) const = 0;
};

namespace object {

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
			return _pimpl->getNode(std::move(params), std::move(idArg));
		}

		service::FieldResult<std::shared_ptr<AppointmentConnection>> getAppointments(service::FieldParams&& params, std::optional<response::IntType>&& firstArg, std::optional<response::Value>&& afterArg, std::optional<response::IntType>&& lastArg, std::optional<response::Value>&& beforeArg) const final
		{
			return _pimpl->getAppointments(std::move(params), std::move(firstArg), std::move(afterArg), std::move(lastArg), std::move(beforeArg));
		}

		service::FieldResult<std::shared_ptr<TaskConnection>> getTasks(service::FieldParams&& params, std::optional<response::IntType>&& firstArg, std::optional<response::Value>&& afterArg, std::optional<response::IntType>&& lastArg, std::optional<response::Value>&& beforeArg) const final
		{
			return _pimpl->getTasks(std::move(params), std::move(firstArg), std::move(afterArg), std::move(lastArg), std::move(beforeArg));
		}

		service::FieldResult<std::shared_ptr<FolderConnection>> getUnreadCounts(service::FieldParams&& params, std::optional<response::IntType>&& firstArg, std::optional<response::Value>&& afterArg, std::optional<response::IntType>&& lastArg, std::optional<response::Value>&& beforeArg) const final
		{
			return _pimpl->getUnreadCounts(std::move(params), std::move(firstArg), std::move(afterArg), std::move(lastArg), std::move(beforeArg));
		}

		service::FieldResult<std::vector<std::shared_ptr<Appointment>>> getAppointmentsById(service::FieldParams&& params, std::vector<response::IdType>&& idsArg) const final
		{
			return _pimpl->getAppointmentsById(std::move(params), std::move(idsArg));
		}

		service::FieldResult<std::vector<std::shared_ptr<Task>>> getTasksById(service::FieldParams&& params, std::vector<response::IdType>&& idsArg) const final
		{
			return _pimpl->getTasksById(std::move(params), std::move(idsArg));
		}

		service::FieldResult<std::vector<std::shared_ptr<Folder>>> getUnreadCountsById(service::FieldParams&& params, std::vector<response::IdType>&& idsArg) const final
		{
			return _pimpl->getUnreadCountsById(std::move(params), std::move(idsArg));
		}

		service::FieldResult<std::shared_ptr<NestedType>> getNested(service::FieldParams&& params) const final
		{
			return _pimpl->getNested(std::move(params));
		}

		service::FieldResult<response::StringType> getUnimplemented(service::FieldParams&& params) const final
		{
			return _pimpl->getUnimplemented(std::move(params));
		}

		service::FieldResult<std::vector<std::shared_ptr<Expensive>>> getExpensive(service::FieldParams&& params) const final
		{
			return _pimpl->getExpensive(std::move(params));
		}

		service::FieldResult<TaskState> getTestTaskState(service::FieldParams&& params) const final
		{
			return _pimpl->getTestTaskState(std::move(params));
		}

		service::FieldResult<std::vector<std::shared_ptr<service::Object>>> getAnyType(service::FieldParams&& params, std::vector<response::IdType>&& idsArg) const final
		{
			return _pimpl->getAnyType(std::move(params), std::move(idsArg));
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

	~Query();
};

class PageInfo
	: public service::Object
{
private:
	service::AwaitableResolver resolveHasNextPage(service::ResolverParams&& params);
	service::AwaitableResolver resolveHasPreviousPage(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<response::BooleanType> getHasNextPage(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<response::BooleanType> getHasPreviousPage(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<response::BooleanType> getHasNextPage(service::FieldParams&& params) const final
		{
			return _pimpl->getHasNextPage(std::move(params));
		}

		service::FieldResult<response::BooleanType> getHasPreviousPage(service::FieldParams&& params) const final
		{
			return _pimpl->getHasPreviousPage(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	PageInfo(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	PageInfo(std::shared_ptr<T> pimpl)
		: PageInfo { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~PageInfo();
};

class AppointmentEdge
	: public service::Object
{
private:
	service::AwaitableResolver resolveNode(service::ResolverParams&& params);
	service::AwaitableResolver resolveCursor(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::shared_ptr<Appointment>> getNode(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<response::Value> getCursor(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<std::shared_ptr<Appointment>> getNode(service::FieldParams&& params) const final
		{
			return _pimpl->getNode(std::move(params));
		}

		service::FieldResult<response::Value> getCursor(service::FieldParams&& params) const final
		{
			return _pimpl->getCursor(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	AppointmentEdge(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	AppointmentEdge(std::shared_ptr<T> pimpl)
		: AppointmentEdge { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~AppointmentEdge();
};

class AppointmentConnection
	: public service::Object
{
private:
	service::AwaitableResolver resolvePageInfo(service::ResolverParams&& params);
	service::AwaitableResolver resolveEdges(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::shared_ptr<PageInfo>> getPageInfo(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<std::optional<std::vector<std::shared_ptr<AppointmentEdge>>>> getEdges(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<std::shared_ptr<PageInfo>> getPageInfo(service::FieldParams&& params) const final
		{
			return _pimpl->getPageInfo(std::move(params));
		}

		service::FieldResult<std::optional<std::vector<std::shared_ptr<AppointmentEdge>>>> getEdges(service::FieldParams&& params) const final
		{
			return _pimpl->getEdges(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	AppointmentConnection(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	AppointmentConnection(std::shared_ptr<T> pimpl)
		: AppointmentConnection { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~AppointmentConnection();
};

class TaskEdge
	: public service::Object
{
private:
	service::AwaitableResolver resolveNode(service::ResolverParams&& params);
	service::AwaitableResolver resolveCursor(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::shared_ptr<Task>> getNode(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<response::Value> getCursor(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<std::shared_ptr<Task>> getNode(service::FieldParams&& params) const final
		{
			return _pimpl->getNode(std::move(params));
		}

		service::FieldResult<response::Value> getCursor(service::FieldParams&& params) const final
		{
			return _pimpl->getCursor(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	TaskEdge(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	TaskEdge(std::shared_ptr<T> pimpl)
		: TaskEdge { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~TaskEdge();
};

class TaskConnection
	: public service::Object
{
private:
	service::AwaitableResolver resolvePageInfo(service::ResolverParams&& params);
	service::AwaitableResolver resolveEdges(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::shared_ptr<PageInfo>> getPageInfo(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<std::optional<std::vector<std::shared_ptr<TaskEdge>>>> getEdges(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<std::shared_ptr<PageInfo>> getPageInfo(service::FieldParams&& params) const final
		{
			return _pimpl->getPageInfo(std::move(params));
		}

		service::FieldResult<std::optional<std::vector<std::shared_ptr<TaskEdge>>>> getEdges(service::FieldParams&& params) const final
		{
			return _pimpl->getEdges(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	TaskConnection(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	TaskConnection(std::shared_ptr<T> pimpl)
		: TaskConnection { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~TaskConnection();
};

class FolderEdge
	: public service::Object
{
private:
	service::AwaitableResolver resolveNode(service::ResolverParams&& params);
	service::AwaitableResolver resolveCursor(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::shared_ptr<Folder>> getNode(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<response::Value> getCursor(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<std::shared_ptr<Folder>> getNode(service::FieldParams&& params) const final
		{
			return _pimpl->getNode(std::move(params));
		}

		service::FieldResult<response::Value> getCursor(service::FieldParams&& params) const final
		{
			return _pimpl->getCursor(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	FolderEdge(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	FolderEdge(std::shared_ptr<T> pimpl)
		: FolderEdge { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~FolderEdge();
};

class FolderConnection
	: public service::Object
{
private:
	service::AwaitableResolver resolvePageInfo(service::ResolverParams&& params);
	service::AwaitableResolver resolveEdges(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::shared_ptr<PageInfo>> getPageInfo(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<std::optional<std::vector<std::shared_ptr<FolderEdge>>>> getEdges(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<std::shared_ptr<PageInfo>> getPageInfo(service::FieldParams&& params) const final
		{
			return _pimpl->getPageInfo(std::move(params));
		}

		service::FieldResult<std::optional<std::vector<std::shared_ptr<FolderEdge>>>> getEdges(service::FieldParams&& params) const final
		{
			return _pimpl->getEdges(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	FolderConnection(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	FolderConnection(std::shared_ptr<T> pimpl)
		: FolderConnection { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~FolderConnection();
};

class CompleteTaskPayload
	: public service::Object
{
private:
	service::AwaitableResolver resolveTask(service::ResolverParams&& params);
	service::AwaitableResolver resolveClientMutationId(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::shared_ptr<Task>> getTask(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<std::optional<response::StringType>> getClientMutationId(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<std::shared_ptr<Task>> getTask(service::FieldParams&& params) const final
		{
			return _pimpl->getTask(std::move(params));
		}

		service::FieldResult<std::optional<response::StringType>> getClientMutationId(service::FieldParams&& params) const final
		{
			return _pimpl->getClientMutationId(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	CompleteTaskPayload(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	CompleteTaskPayload(std::shared_ptr<T> pimpl)
		: CompleteTaskPayload { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~CompleteTaskPayload();
};

class Mutation
	: public service::Object
{
private:
	service::AwaitableResolver resolveCompleteTask(service::ResolverParams&& params);
	service::AwaitableResolver resolveSetFloat(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::shared_ptr<CompleteTaskPayload>> applyCompleteTask(service::FieldParams&& params, CompleteTaskInput&& inputArg) const = 0;
		virtual service::FieldResult<response::FloatType> applySetFloat(service::FieldParams&& params, response::FloatType&& valueArg) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<std::shared_ptr<CompleteTaskPayload>> applyCompleteTask(service::FieldParams&& params, CompleteTaskInput&& inputArg) const final
		{
			return _pimpl->applyCompleteTask(std::move(params), std::move(inputArg));
		}

		service::FieldResult<response::FloatType> applySetFloat(service::FieldParams&& params, response::FloatType&& valueArg) const final
		{
			return _pimpl->applySetFloat(std::move(params), std::move(valueArg));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Mutation(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	Mutation(std::shared_ptr<T> pimpl)
		: Mutation { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~Mutation();
};

class Subscription
	: public service::Object
{
private:
	service::AwaitableResolver resolveNextAppointmentChange(service::ResolverParams&& params);
	service::AwaitableResolver resolveNodeChange(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::shared_ptr<Appointment>> getNextAppointmentChange(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<std::shared_ptr<service::Object>> getNodeChange(service::FieldParams&& params, response::IdType&& idArg) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<std::shared_ptr<Appointment>> getNextAppointmentChange(service::FieldParams&& params) const final
		{
			return _pimpl->getNextAppointmentChange(std::move(params));
		}

		service::FieldResult<std::shared_ptr<service::Object>> getNodeChange(service::FieldParams&& params, response::IdType&& idArg) const final
		{
			return _pimpl->getNodeChange(std::move(params), std::move(idArg));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Subscription(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	Subscription(std::shared_ptr<T> pimpl)
		: Subscription { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~Subscription();
};

class Appointment
	: public service::Object
{
private:
	service::AwaitableResolver resolveId(service::ResolverParams&& params);
	service::AwaitableResolver resolveWhen(service::ResolverParams&& params);
	service::AwaitableResolver resolveSubject(service::ResolverParams&& params);
	service::AwaitableResolver resolveIsNow(service::ResolverParams&& params);
	service::AwaitableResolver resolveForceError(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
		: Node
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::optional<response::Value>> getWhen(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<std::optional<response::StringType>> getSubject(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<response::BooleanType> getIsNow(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<std::optional<response::StringType>> getForceError(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<response::IdType> getId(service::FieldParams&& params) const final
		{
			return _pimpl->getId(std::move(params));
		}

		service::FieldResult<std::optional<response::Value>> getWhen(service::FieldParams&& params) const final
		{
			return _pimpl->getWhen(std::move(params));
		}

		service::FieldResult<std::optional<response::StringType>> getSubject(service::FieldParams&& params) const final
		{
			return _pimpl->getSubject(std::move(params));
		}

		service::FieldResult<response::BooleanType> getIsNow(service::FieldParams&& params) const final
		{
			return _pimpl->getIsNow(std::move(params));
		}

		service::FieldResult<std::optional<response::StringType>> getForceError(service::FieldParams&& params) const final
		{
			return _pimpl->getForceError(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Appointment(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	Appointment(std::shared_ptr<T> pimpl)
		: Appointment { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~Appointment();
};

class Task
	: public service::Object
{
private:
	service::AwaitableResolver resolveId(service::ResolverParams&& params);
	service::AwaitableResolver resolveTitle(service::ResolverParams&& params);
	service::AwaitableResolver resolveIsComplete(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
		: Node
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::optional<response::StringType>> getTitle(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<response::BooleanType> getIsComplete(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<response::IdType> getId(service::FieldParams&& params) const final
		{
			return _pimpl->getId(std::move(params));
		}

		service::FieldResult<std::optional<response::StringType>> getTitle(service::FieldParams&& params) const final
		{
			return _pimpl->getTitle(std::move(params));
		}

		service::FieldResult<response::BooleanType> getIsComplete(service::FieldParams&& params) const final
		{
			return _pimpl->getIsComplete(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Task(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	Task(std::shared_ptr<T> pimpl)
		: Task { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~Task();
};

class Folder
	: public service::Object
{
private:
	service::AwaitableResolver resolveId(service::ResolverParams&& params);
	service::AwaitableResolver resolveName(service::ResolverParams&& params);
	service::AwaitableResolver resolveUnreadCount(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
		: Node
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::optional<response::StringType>> getName(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<response::IntType> getUnreadCount(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<response::IdType> getId(service::FieldParams&& params) const final
		{
			return _pimpl->getId(std::move(params));
		}

		service::FieldResult<std::optional<response::StringType>> getName(service::FieldParams&& params) const final
		{
			return _pimpl->getName(std::move(params));
		}

		service::FieldResult<response::IntType> getUnreadCount(service::FieldParams&& params) const final
		{
			return _pimpl->getUnreadCount(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Folder(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	Folder(std::shared_ptr<T> pimpl)
		: Folder { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~Folder();
};

class NestedType
	: public service::Object
{
private:
	service::AwaitableResolver resolveDepth(service::ResolverParams&& params);
	service::AwaitableResolver resolveNested(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<response::IntType> getDepth(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<std::shared_ptr<NestedType>> getNested(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<response::IntType> getDepth(service::FieldParams&& params) const final
		{
			return _pimpl->getDepth(std::move(params));
		}

		service::FieldResult<std::shared_ptr<NestedType>> getNested(service::FieldParams&& params) const final
		{
			return _pimpl->getNested(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	NestedType(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	NestedType(std::shared_ptr<T> pimpl)
		: NestedType { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~NestedType();
};

class Expensive
	: public service::Object
{
private:
	service::AwaitableResolver resolveOrder(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<response::IntType> getOrder(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<response::IntType> getOrder(service::FieldParams&& params) const final
		{
			return _pimpl->getOrder(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Expensive(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	Expensive(std::shared_ptr<T> pimpl)
		: Expensive { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~Expensive();
};

} // namespace object

class Operations
	: public service::Request
{
public:
	explicit Operations(std::shared_ptr<object::Query> query, std::shared_ptr<object::Mutation> mutation, std::shared_ptr<object::Subscription> subscription);

	template <class TQuery, class TMutation, class TSubscription>
	explicit Operations(std::shared_ptr<TQuery> query, std::shared_ptr<TMutation> mutation, std::shared_ptr<TSubscription> subscription)
		: Operations { std::make_shared<object::Query>(std::move(query)), std::make_shared<object::Mutation>(std::move(mutation)), std::make_shared<object::Subscription>(std::move(subscription)) }
	{
	}

private:
	std::shared_ptr<object::Query> _query;
	std::shared_ptr<object::Mutation> _mutation;
	std::shared_ptr<object::Subscription> _subscription;
};

std::shared_ptr<schema::Schema> GetSchema();

} // namespace today
} // namespace graphql

#endif // TODAYSCHEMA_H
