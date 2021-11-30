// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef COMPLETETASKPAYLOADOBJECT_H
#define COMPLETETASKPAYLOADOBJECT_H

#include "TodaySchema.h"

namespace graphql::today::object {

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

} // namespace graphql::today::object

#endif // COMPLETETASKPAYLOADOBJECT_H
