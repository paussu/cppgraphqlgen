// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "DogObject.h"
#include "HumanObject.h"

#include "graphqlservice/internal/Schema.h"

#include "graphqlservice/introspection/IntrospectionSchema.h"

#include <algorithm>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

using namespace std::literals;

namespace graphql::validation {
namespace object {

Dog::Dog(std::unique_ptr<Concept>&& pimpl) noexcept
	: service::Object{ getTypeNames(), getResolvers() }
	, _pimpl { std::move(pimpl) }
{
}

service::TypeNames Dog::getTypeNames() const noexcept
{
	return {
		R"gql(Pet)gql"sv,
		R"gql(CatOrDog)gql"sv,
		R"gql(DogOrHuman)gql"sv,
		R"gql(Dog)gql"sv
	};
}

service::ResolverMap Dog::getResolvers() const noexcept
{
	return {
		{ R"gql(name)gql"sv, [this](service::ResolverParams&& params) { return resolveName(std::move(params)); } },
		{ R"gql(owner)gql"sv, [this](service::ResolverParams&& params) { return resolveOwner(std::move(params)); } },
		{ R"gql(nickname)gql"sv, [this](service::ResolverParams&& params) { return resolveNickname(std::move(params)); } },
		{ R"gql(__typename)gql"sv, [this](service::ResolverParams&& params) { return resolve_typename(std::move(params)); } },
		{ R"gql(barkVolume)gql"sv, [this](service::ResolverParams&& params) { return resolveBarkVolume(std::move(params)); } },
		{ R"gql(isHousetrained)gql"sv, [this](service::ResolverParams&& params) { return resolveIsHousetrained(std::move(params)); } },
		{ R"gql(doesKnowCommand)gql"sv, [this](service::ResolverParams&& params) { return resolveDoesKnowCommand(std::move(params)); } }
	};
}

void Dog::beginSelectionSet(const service::SelectionSetParams& params) const
{
	_pimpl->beginSelectionSet(params);
}

void Dog::endSelectionSet(const service::SelectionSetParams& params) const
{
	_pimpl->endSelectionSet(params);
}

service::AwaitableResolver Dog::resolveName(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = _pimpl->getName(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<std::string>::convert(std::move(result), std::move(params));
}

service::AwaitableResolver Dog::resolveNickname(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = _pimpl->getNickname(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<std::string>::convert<service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

service::AwaitableResolver Dog::resolveBarkVolume(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = _pimpl->getBarkVolume(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<int>::convert<service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

service::AwaitableResolver Dog::resolveDoesKnowCommand(service::ResolverParams&& params) const
{
	auto argDogCommand = service::ModifiedArgument<DogCommand>::require("dogCommand", params.arguments);
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = _pimpl->getDoesKnowCommand(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)), std::move(argDogCommand));
	resolverLock.unlock();

	return service::ModifiedResult<bool>::convert(std::move(result), std::move(params));
}

service::AwaitableResolver Dog::resolveIsHousetrained(service::ResolverParams&& params) const
{
	auto argAtOtherHomes = service::ModifiedArgument<bool>::require<service::TypeModifier::Nullable>("atOtherHomes", params.arguments);
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = _pimpl->getIsHousetrained(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)), std::move(argAtOtherHomes));
	resolverLock.unlock();

	return service::ModifiedResult<bool>::convert(std::move(result), std::move(params));
}

service::AwaitableResolver Dog::resolveOwner(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = _pimpl->getOwner(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<Human>::convert<service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

service::AwaitableResolver Dog::resolve_typename(service::ResolverParams&& params) const
{
	return service::ModifiedResult<std::string>::convert(std::string{ R"gql(Dog)gql" }, std::move(params));
}

} // namespace object

void AddDogDetails(const std::shared_ptr<schema::ObjectType>& typeDog, const std::shared_ptr<schema::Schema>& schema)
{
	typeDog->AddInterfaces({
		std::static_pointer_cast<const schema::InterfaceType>(schema->LookupType(R"gql(Pet)gql"sv))
	});
	typeDog->AddFields({
		schema::Field::Make(R"gql(name)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType(R"gql(String)gql"sv))),
		schema::Field::Make(R"gql(nickname)gql"sv, R"md()md"sv, std::nullopt, schema->LookupType(R"gql(String)gql"sv)),
		schema::Field::Make(R"gql(barkVolume)gql"sv, R"md()md"sv, std::nullopt, schema->LookupType(R"gql(Int)gql"sv)),
		schema::Field::Make(R"gql(doesKnowCommand)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType(R"gql(Boolean)gql"sv)), {
			schema::InputValue::Make(R"gql(dogCommand)gql"sv, R"md()md"sv, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType(R"gql(DogCommand)gql"sv)), R"gql()gql"sv)
		}),
		schema::Field::Make(R"gql(isHousetrained)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType(R"gql(Boolean)gql"sv)), {
			schema::InputValue::Make(R"gql(atOtherHomes)gql"sv, R"md()md"sv, schema->LookupType(R"gql(Boolean)gql"sv), R"gql()gql"sv)
		}),
		schema::Field::Make(R"gql(owner)gql"sv, R"md()md"sv, std::nullopt, schema->LookupType(R"gql(Human)gql"sv))
	});
}

} // namespace graphql::validation
