// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "DroidObject.h"

#include "graphqlservice/introspection/Introspection.h"

#include <algorithm>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

using namespace std::literals;

namespace graphql::learn {
namespace object {

Droid::Droid()
	: service::Object({
		R"gql(Character)gql"sv,
		R"gql(Droid)gql"sv,
	}, {
		{ R"gql(id)gql"sv, [this](service::ResolverParams&& params) { return resolveId(std::move(params)); } },
		{ R"gql(name)gql"sv, [this](service::ResolverParams&& params) { return resolveName(std::move(params)); } },
		{ R"gql(friends)gql"sv, [this](service::ResolverParams&& params) { return resolveFriends(std::move(params)); } },
		{ R"gql(appearsIn)gql"sv, [this](service::ResolverParams&& params) { return resolveAppearsIn(std::move(params)); } },
		{ R"gql(__typename)gql"sv, [this](service::ResolverParams&& params) { return resolve_typename(std::move(params)); } },
		{ R"gql(primaryFunction)gql"sv, [this](service::ResolverParams&& params) { return resolvePrimaryFunction(std::move(params)); } }
	})
{
}

std::future<service::ResolverResult> Droid::resolveId(service::ResolverParams&& params)
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getId(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<response::StringType>::convert(std::move(result), std::move(params));
}

std::future<service::ResolverResult> Droid::resolveName(service::ResolverParams&& params)
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getName(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<response::StringType>::convert<service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

std::future<service::ResolverResult> Droid::resolveFriends(service::ResolverParams&& params)
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getFriends(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<service::Object>::convert<service::TypeModifier::Nullable, service::TypeModifier::List, service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

std::future<service::ResolverResult> Droid::resolveAppearsIn(service::ResolverParams&& params)
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getAppearsIn(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<Episode>::convert<service::TypeModifier::Nullable, service::TypeModifier::List, service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

std::future<service::ResolverResult> Droid::resolvePrimaryFunction(service::ResolverParams&& params)
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getPrimaryFunction(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<response::StringType>::convert<service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

std::future<service::ResolverResult> Droid::resolve_typename(service::ResolverParams&& params)
{
	return service::ModifiedResult<response::StringType>::convert(response::StringType{ R"gql(Droid)gql" }, std::move(params));
}

} // namespace object

void AddDroidDetails(std::shared_ptr<schema::ObjectType> typeDroid, const std::shared_ptr<schema::Schema>& schema)
{
	typeDroid->AddInterfaces({
		std::static_pointer_cast<const schema::InterfaceType>(schema->LookupType(R"gql(Character)gql"sv))
	});
	typeDroid->AddFields({
		schema::Field::Make(R"gql(id)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("String"))),
		schema::Field::Make(R"gql(name)gql"sv, R"md()md"sv, std::nullopt, schema->LookupType("String")),
		schema::Field::Make(R"gql(friends)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::LIST, schema->LookupType("Character"))),
		schema::Field::Make(R"gql(appearsIn)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::LIST, schema->LookupType("Episode"))),
		schema::Field::Make(R"gql(primaryFunction)gql"sv, R"md()md"sv, std::nullopt, schema->LookupType("String"))
	});
}

} // namespace graphql::learn
