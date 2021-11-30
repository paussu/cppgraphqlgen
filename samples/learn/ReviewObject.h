// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef REVIEWOBJECT_H
#define REVIEWOBJECT_H

#include "StarWarsSchema.h"

namespace graphql::learn::object {

class Review
	: public service::Object
{
private:
	service::AwaitableResolver resolveStars(service::ResolverParams&& params);
	service::AwaitableResolver resolveCommentary(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<response::IntType> getStars(service::FieldParams&& params) const = 0;
		virtual service::FieldResult<std::optional<response::StringType>> getCommentary(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<response::IntType> getStars(service::FieldParams&& params) const final
		{
			return _pimpl->getStars(std::move(params));
		}

		service::FieldResult<std::optional<response::StringType>> getCommentary(service::FieldParams&& params) const final
		{
			return _pimpl->getCommentary(std::move(params));
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Review(std::unique_ptr<Concept>&& pimpl);

	const std::unique_ptr<Concept> _pimpl;

public:
	template <class T>
	Review(std::shared_ptr<T> pimpl)
		: Review { std::unique_ptr<Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	~Review();
};

} // namespace graphql::learn::object

#endif // REVIEWOBJECT_H
