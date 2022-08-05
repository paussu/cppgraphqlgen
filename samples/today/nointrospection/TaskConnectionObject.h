// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef TASKCONNECTIONOBJECT_H
#define TASKCONNECTIONOBJECT_H

#include "TodaySchema.h"

namespace graphql::today::object {
namespace methods::TaskConnectionHas {

template <class TImpl>
concept getPageInfoWithParams = requires (TImpl impl, service::FieldParams params)
{
	{ service::AwaitableObject<std::shared_ptr<PageInfo>> { impl.getPageInfo(std::move(params)) } };
};

template <class TImpl>
concept getPageInfo = requires (TImpl impl)
{
	{ service::AwaitableObject<std::shared_ptr<PageInfo>> { impl.getPageInfo() } };
};

template <class TImpl>
concept getEdgesWithParams = requires (TImpl impl, service::FieldParams params)
{
	{ service::AwaitableObject<std::optional<std::vector<std::shared_ptr<TaskEdge>>>> { impl.getEdges(std::move(params)) } };
};

template <class TImpl>
concept getEdges = requires (TImpl impl)
{
	{ service::AwaitableObject<std::optional<std::vector<std::shared_ptr<TaskEdge>>>> { impl.getEdges() } };
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

} // namespace methods::TaskConnectionHas

class [[nodiscard]] TaskConnection final
	: public service::Object
{
private:
	[[nodiscard]] service::AwaitableResolver resolvePageInfo(service::ResolverParams&& params) const;
	[[nodiscard]] service::AwaitableResolver resolveEdges(service::ResolverParams&& params) const;

	[[nodiscard]] service::AwaitableResolver resolve_typename(service::ResolverParams&& params) const;

	struct [[nodiscard]] Concept
	{
		virtual ~Concept() = default;

		virtual void beginSelectionSet(const service::SelectionSetParams& params) const = 0;
		virtual void endSelectionSet(const service::SelectionSetParams& params) const = 0;

		[[nodiscard]] virtual service::AwaitableObject<std::shared_ptr<PageInfo>> getPageInfo(service::FieldParams&& params) const = 0;
		[[nodiscard]] virtual service::AwaitableObject<std::optional<std::vector<std::shared_ptr<TaskEdge>>>> getEdges(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct [[nodiscard]] Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		[[nodiscard]] service::AwaitableObject<std::shared_ptr<PageInfo>> getPageInfo(service::FieldParams&& params) const final
		{
			if constexpr (methods::TaskConnectionHas::getPageInfoWithParams<T>)
			{
				return { _pimpl->getPageInfo(std::move(params)) };
			}
			else if constexpr (methods::TaskConnectionHas::getPageInfo<T>)
			{
				return { _pimpl->getPageInfo() };
			}
			else
			{
				throw std::runtime_error(R"ex(TaskConnection::getPageInfo is not implemented)ex");
			}
		}

		[[nodiscard]] service::AwaitableObject<std::optional<std::vector<std::shared_ptr<TaskEdge>>>> getEdges(service::FieldParams&& params) const final
		{
			if constexpr (methods::TaskConnectionHas::getEdgesWithParams<T>)
			{
				return { _pimpl->getEdges(std::move(params)) };
			}
			else if constexpr (methods::TaskConnectionHas::getEdges<T>)
			{
				return { _pimpl->getEdges() };
			}
			else
			{
				throw std::runtime_error(R"ex(TaskConnection::getEdges is not implemented)ex");
			}
		}

		void beginSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::TaskConnectionHas::beginSelectionSet<T>)
			{
				_pimpl->beginSelectionSet(params);
			}
		}

		void endSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::TaskConnectionHas::endSelectionSet<T>)
			{
				_pimpl->endSelectionSet(params);
			}
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	TaskConnection(std::unique_ptr<const Concept>&& pimpl) noexcept;

	[[nodiscard]] service::TypeNames getTypeNames() const noexcept;
	[[nodiscard]] service::ResolverMap getResolvers() const noexcept;

	void beginSelectionSet(const service::SelectionSetParams& params) const override;
	void endSelectionSet(const service::SelectionSetParams& params) const override;

	const std::unique_ptr<const Concept> _pimpl;

public:
	template <class T>
	TaskConnection(std::shared_ptr<T> pimpl) noexcept
		: TaskConnection { std::unique_ptr<const Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	[[nodiscard]] static constexpr std::string_view getObjectType() noexcept
	{
		return { R"gql(TaskConnection)gql" };
	}
};

} // namespace graphql::today::object

#endif // TASKCONNECTIONOBJECT_H
