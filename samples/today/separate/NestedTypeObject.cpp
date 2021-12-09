// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "NestedTypeObject.h"
#include "NestedTypeObject.h"

#include "graphqlservice/introspection/Introspection.h"

#include <algorithm>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

using namespace std::literals;

namespace graphql::today {
namespace object {

NestedType::NestedType()
	: service::Object({
		R"gql(NestedType)gql"sv,
	}, {
		{ R"gql(depth)gql"sv, [this](service::ResolverParams&& params) { return resolveDepth(std::move(params)); } },
		{ R"gql(nested)gql"sv, [this](service::ResolverParams&& params) { return resolveNested(std::move(params)); } },
		{ R"gql(__typename)gql"sv, [this](service::ResolverParams&& params) { return resolve_typename(std::move(params)); } }
	})
{
}

service::FieldResult<response::IntType> NestedType::getDepth(service::FieldParams&&) const
{
	throw std::runtime_error(R"ex(NestedType::getDepth is not implemented)ex");
}

std::future<service::ResolverResult> NestedType::resolveDepth(service::ResolverParams&& params)
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getDepth(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<response::IntType>::convert(std::move(result), std::move(params));
}

service::FieldResult<std::shared_ptr<NestedType>> NestedType::getNested(service::FieldParams&&) const
{
	throw std::runtime_error(R"ex(NestedType::getNested is not implemented)ex");
}

std::future<service::ResolverResult> NestedType::resolveNested(service::ResolverParams&& params)
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getNested(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<NestedType>::convert(std::move(result), std::move(params));
}

std::future<service::ResolverResult> NestedType::resolve_typename(service::ResolverParams&& params)
{
	return service::ModifiedResult<response::StringType>::convert(response::StringType{ R"gql(NestedType)gql" }, std::move(params));
}

} // namespace object

void AddNestedTypeDetails(std::shared_ptr<schema::ObjectType> typeNestedType, const std::shared_ptr<schema::Schema>& schema)
{
	typeNestedType->AddFields({
		schema::Field::Make(R"gql(depth)gql"sv, R"md(Depth of the nested element)md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("Int"))),
		schema::Field::Make(R"gql(nested)gql"sv, R"md(Link to the next level)md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("NestedType")))
	});
}

} // namespace graphql::today
