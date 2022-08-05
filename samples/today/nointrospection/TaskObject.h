// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef TASKOBJECT_H
#define TASKOBJECT_H

#include "TodaySchema.h"

namespace graphql::today::object {
namespace implements {

template <class I>
concept TaskIs = std::is_same_v<I, Node> || std::is_same_v<I, UnionType>;

} // namespace implements

namespace methods::TaskHas {

template <class TImpl>
concept getIdWithParams = requires (TImpl impl, service::FieldParams params)
{
	{ service::AwaitableScalar<response::IdType> { impl.getId(std::move(params)) } };
};

template <class TImpl>
concept getId = requires (TImpl impl)
{
	{ service::AwaitableScalar<response::IdType> { impl.getId() } };
};

template <class TImpl>
concept getTitleWithParams = requires (TImpl impl, service::FieldParams params)
{
	{ service::AwaitableScalar<std::optional<std::string>> { impl.getTitle(std::move(params)) } };
};

template <class TImpl>
concept getTitle = requires (TImpl impl)
{
	{ service::AwaitableScalar<std::optional<std::string>> { impl.getTitle() } };
};

template <class TImpl>
concept getIsCompleteWithParams = requires (TImpl impl, service::FieldParams params)
{
	{ service::AwaitableScalar<bool> { impl.getIsComplete(std::move(params)) } };
};

template <class TImpl>
concept getIsComplete = requires (TImpl impl)
{
	{ service::AwaitableScalar<bool> { impl.getIsComplete() } };
};

template <class TImpl>
concept beginSelectionSet = requires (TImpl impl, const service::SelectionSetParams params)
{
	{ impl.beginSelectionSet(params) };
};

template <class TImpl>
concept endSelectionSet = requires (TImpl impl, const service::SelectionSetParams params)
{
	{ impl.endSelectionSet(params) };
};

} // namespace methods::TaskHas

class [[nodiscard]] Task final
	: public service::Object
{
private:
	[[nodiscard]] service::AwaitableResolver resolveId(service::ResolverParams&& params) const;
	[[nodiscard]] service::AwaitableResolver resolveTitle(service::ResolverParams&& params) const;
	[[nodiscard]] service::AwaitableResolver resolveIsComplete(service::ResolverParams&& params) const;

	[[nodiscard]] service::AwaitableResolver resolve_typename(service::ResolverParams&& params) const;

	struct [[nodiscard]] Concept
	{
		virtual ~Concept() = default;

		virtual void beginSelectionSet(const service::SelectionSetParams& params) const = 0;
		virtual void endSelectionSet(const service::SelectionSetParams& params) const = 0;

		[[nodiscard]] virtual service::AwaitableScalar<response::IdType> getId(service::FieldParams&& params) const = 0;
		[[nodiscard]] virtual service::AwaitableScalar<std::optional<std::string>> getTitle(service::FieldParams&& params) const = 0;
		[[nodiscard]] virtual service::AwaitableScalar<bool> getIsComplete(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct [[nodiscard]] Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		[[nodiscard]] service::AwaitableScalar<response::IdType> getId(service::FieldParams&& params) const final
		{
			if constexpr (methods::TaskHas::getIdWithParams<T>)
			{
				return { _pimpl->getId(std::move(params)) };
			}
			else if constexpr (methods::TaskHas::getId<T>)
			{
				return { _pimpl->getId() };
			}
			else
			{
				throw std::runtime_error(R"ex(Task::getId is not implemented)ex");
			}
		}

		[[nodiscard]] service::AwaitableScalar<std::optional<std::string>> getTitle(service::FieldParams&& params) const final
		{
			if constexpr (methods::TaskHas::getTitleWithParams<T>)
			{
				return { _pimpl->getTitle(std::move(params)) };
			}
			else if constexpr (methods::TaskHas::getTitle<T>)
			{
				return { _pimpl->getTitle() };
			}
			else
			{
				throw std::runtime_error(R"ex(Task::getTitle is not implemented)ex");
			}
		}

		[[nodiscard]] service::AwaitableScalar<bool> getIsComplete(service::FieldParams&& params) const final
		{
			if constexpr (methods::TaskHas::getIsCompleteWithParams<T>)
			{
				return { _pimpl->getIsComplete(std::move(params)) };
			}
			else if constexpr (methods::TaskHas::getIsComplete<T>)
			{
				return { _pimpl->getIsComplete() };
			}
			else
			{
				throw std::runtime_error(R"ex(Task::getIsComplete is not implemented)ex");
			}
		}

		void beginSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::TaskHas::beginSelectionSet<T>)
			{
				_pimpl->beginSelectionSet(params);
			}
		}

		void endSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::TaskHas::endSelectionSet<T>)
			{
				_pimpl->endSelectionSet(params);
			}
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Task(std::unique_ptr<const Concept>&& pimpl) noexcept;

	// Interfaces which this type implements
	friend Node;

	// Unions which include this type
	friend UnionType;

	template <class I>
	[[nodiscard]] static constexpr bool implements() noexcept
	{
		return implements::TaskIs<I>;
	}

	[[nodiscard]] service::TypeNames getTypeNames() const noexcept;
	[[nodiscard]] service::ResolverMap getResolvers() const noexcept;

	void beginSelectionSet(const service::SelectionSetParams& params) const override;
	void endSelectionSet(const service::SelectionSetParams& params) const override;

	const std::unique_ptr<const Concept> _pimpl;

public:
	template <class T>
	Task(std::shared_ptr<T> pimpl) noexcept
		: Task { std::unique_ptr<const Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	[[nodiscard]] static constexpr std::string_view getObjectType() noexcept
	{
		return { R"gql(Task)gql" };
	}
};

} // namespace graphql::today::object

#endif // TASKOBJECT_H
