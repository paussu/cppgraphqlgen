// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef MUTATIONOBJECT_H
#define MUTATIONOBJECT_H

#include "StarWarsSchema.h"

namespace graphql::learn::object {

class Mutation
	: public service::Object
{
private:
	service::AwaitableResolver resolveCreateReview(service::ResolverParams&& params);

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params);

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::FieldResult<std::shared_ptr<Review>> applyCreateReview(service::FieldParams&& params, Episode&& epArg, ReviewInput&& reviewArg) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::FieldResult<std::shared_ptr<Review>> applyCreateReview(service::FieldParams&& params, Episode&& epArg, ReviewInput&& reviewArg) const final
		{
			return _pimpl->applyCreateReview(std::move(params), std::move(epArg), std::move(reviewArg));
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

} // namespace graphql::learn::object

#endif // MUTATIONOBJECT_H
