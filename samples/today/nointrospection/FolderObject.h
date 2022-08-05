// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef FOLDEROBJECT_H
#define FOLDEROBJECT_H

#include "TodaySchema.h"

namespace graphql::today::object {
namespace implements {

template <class I>
concept FolderIs = std::is_same_v<I, Node> || std::is_same_v<I, UnionType>;

} // namespace implements

namespace methods::FolderHas {

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
concept getNameWithParams = requires (TImpl impl, service::FieldParams params)
{
	{ service::AwaitableScalar<std::optional<std::string>> { impl.getName(std::move(params)) } };
};

template <class TImpl>
concept getName = requires (TImpl impl)
{
	{ service::AwaitableScalar<std::optional<std::string>> { impl.getName() } };
};

template <class TImpl>
concept getUnreadCountWithParams = requires (TImpl impl, service::FieldParams params)
{
	{ service::AwaitableScalar<int> { impl.getUnreadCount(std::move(params)) } };
};

template <class TImpl>
concept getUnreadCount = requires (TImpl impl)
{
	{ service::AwaitableScalar<int> { impl.getUnreadCount() } };
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

} // namespace methods::FolderHas

class [[nodiscard]] Folder final
	: public service::Object
{
private:
	[[nodiscard]] service::AwaitableResolver resolveId(service::ResolverParams&& params) const;
	[[nodiscard]] service::AwaitableResolver resolveName(service::ResolverParams&& params) const;
	[[nodiscard]] service::AwaitableResolver resolveUnreadCount(service::ResolverParams&& params) const;

	[[nodiscard]] service::AwaitableResolver resolve_typename(service::ResolverParams&& params) const;

	struct [[nodiscard]] Concept
	{
		virtual ~Concept() = default;

		virtual void beginSelectionSet(const service::SelectionSetParams& params) const = 0;
		virtual void endSelectionSet(const service::SelectionSetParams& params) const = 0;

		[[nodiscard]] virtual service::AwaitableScalar<response::IdType> getId(service::FieldParams&& params) const = 0;
		[[nodiscard]] virtual service::AwaitableScalar<std::optional<std::string>> getName(service::FieldParams&& params) const = 0;
		[[nodiscard]] virtual service::AwaitableScalar<int> getUnreadCount(service::FieldParams&& params) const = 0;
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
			if constexpr (methods::FolderHas::getIdWithParams<T>)
			{
				return { _pimpl->getId(std::move(params)) };
			}
			else if constexpr (methods::FolderHas::getId<T>)
			{
				return { _pimpl->getId() };
			}
			else
			{
				throw std::runtime_error(R"ex(Folder::getId is not implemented)ex");
			}
		}

		[[nodiscard]] service::AwaitableScalar<std::optional<std::string>> getName(service::FieldParams&& params) const final
		{
			if constexpr (methods::FolderHas::getNameWithParams<T>)
			{
				return { _pimpl->getName(std::move(params)) };
			}
			else if constexpr (methods::FolderHas::getName<T>)
			{
				return { _pimpl->getName() };
			}
			else
			{
				throw std::runtime_error(R"ex(Folder::getName is not implemented)ex");
			}
		}

		[[nodiscard]] service::AwaitableScalar<int> getUnreadCount(service::FieldParams&& params) const final
		{
			if constexpr (methods::FolderHas::getUnreadCountWithParams<T>)
			{
				return { _pimpl->getUnreadCount(std::move(params)) };
			}
			else if constexpr (methods::FolderHas::getUnreadCount<T>)
			{
				return { _pimpl->getUnreadCount() };
			}
			else
			{
				throw std::runtime_error(R"ex(Folder::getUnreadCount is not implemented)ex");
			}
		}

		void beginSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::FolderHas::beginSelectionSet<T>)
			{
				_pimpl->beginSelectionSet(params);
			}
		}

		void endSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::FolderHas::endSelectionSet<T>)
			{
				_pimpl->endSelectionSet(params);
			}
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Folder(std::unique_ptr<const Concept>&& pimpl) noexcept;

	// Interfaces which this type implements
	friend Node;

	// Unions which include this type
	friend UnionType;

	template <class I>
	[[nodiscard]] static constexpr bool implements() noexcept
	{
		return implements::FolderIs<I>;
	}

	[[nodiscard]] service::TypeNames getTypeNames() const noexcept;
	[[nodiscard]] service::ResolverMap getResolvers() const noexcept;

	void beginSelectionSet(const service::SelectionSetParams& params) const override;
	void endSelectionSet(const service::SelectionSetParams& params) const override;

	const std::unique_ptr<const Concept> _pimpl;

public:
	template <class T>
	Folder(std::shared_ptr<T> pimpl) noexcept
		: Folder { std::unique_ptr<const Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	[[nodiscard]] static constexpr std::string_view getObjectType() noexcept
	{
		return { R"gql(Folder)gql" };
	}
};

} // namespace graphql::today::object

#endif // FOLDEROBJECT_H
