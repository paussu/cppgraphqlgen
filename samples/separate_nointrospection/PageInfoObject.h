// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef PAGEINFOOBJECT_H
#define PAGEINFOOBJECT_H

#include "TodaySchema.h"

namespace graphql::today::object {

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

} // namespace graphql::today::object

#endif // PAGEINFOOBJECT_H
