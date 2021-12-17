// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef TYPEOBJECT_H
#define TYPEOBJECT_H

#include "IntrospectionSchema.h"

namespace graphql::introspection::object {

class Type
	: public service::Object
{
private:
	service::AwaitableResolver resolveKind(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveName(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveDescription(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveFields(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveInterfaces(service::ResolverParams&& params) const;
	service::AwaitableResolver resolvePossibleTypes(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveEnumValues(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveInputFields(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveOfType(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveSpecifiedByURL(service::ResolverParams&& params) const;

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params) const;

	struct Concept
	{
		virtual ~Concept() = default;

		virtual service::AwaitableScalar<TypeKind> getKind() const = 0;
		virtual service::AwaitableScalar<std::optional<std::string>> getName() const = 0;
		virtual service::AwaitableScalar<std::optional<std::string>> getDescription() const = 0;
		virtual service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Field>>>> getFields(std::optional<bool>&& includeDeprecatedArg) const = 0;
		virtual service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Type>>>> getInterfaces() const = 0;
		virtual service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Type>>>> getPossibleTypes() const = 0;
		virtual service::AwaitableObject<std::optional<std::vector<std::shared_ptr<EnumValue>>>> getEnumValues(std::optional<bool>&& includeDeprecatedArg) const = 0;
		virtual service::AwaitableObject<std::optional<std::vector<std::shared_ptr<InputValue>>>> getInputFields() const = 0;
		virtual service::AwaitableObject<std::shared_ptr<Type>> getOfType() const = 0;
		virtual service::AwaitableScalar<std::optional<std::string>> getSpecifiedByURL() const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::AwaitableScalar<TypeKind> getKind() const final
		{
			return { _pimpl->getKind() };
		}

		service::AwaitableScalar<std::optional<std::string>> getName() const final
		{
			return { _pimpl->getName() };
		}

		service::AwaitableScalar<std::optional<std::string>> getDescription() const final
		{
			return { _pimpl->getDescription() };
		}

		service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Field>>>> getFields(std::optional<bool>&& includeDeprecatedArg) const final
		{
			return { _pimpl->getFields(std::move(includeDeprecatedArg)) };
		}

		service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Type>>>> getInterfaces() const final
		{
			return { _pimpl->getInterfaces() };
		}

		service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Type>>>> getPossibleTypes() const final
		{
			return { _pimpl->getPossibleTypes() };
		}

		service::AwaitableObject<std::optional<std::vector<std::shared_ptr<EnumValue>>>> getEnumValues(std::optional<bool>&& includeDeprecatedArg) const final
		{
			return { _pimpl->getEnumValues(std::move(includeDeprecatedArg)) };
		}

		service::AwaitableObject<std::optional<std::vector<std::shared_ptr<InputValue>>>> getInputFields() const final
		{
			return { _pimpl->getInputFields() };
		}

		service::AwaitableObject<std::shared_ptr<Type>> getOfType() const final
		{
			return { _pimpl->getOfType() };
		}

		service::AwaitableScalar<std::optional<std::string>> getSpecifiedByURL() const final
		{
			return { _pimpl->getSpecifiedByURL() };
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	const std::unique_ptr<Concept> _pimpl;

	service::TypeNames getTypeNames() const noexcept;
	service::ResolverMap getResolvers() const noexcept;

public:
	GRAPHQLINTROSPECTION_EXPORT Type(std::shared_ptr<introspection::Type> pimpl) noexcept;
	GRAPHQLINTROSPECTION_EXPORT ~Type();
};

} // namespace graphql::introspection::object

#endif // TYPEOBJECT_H
