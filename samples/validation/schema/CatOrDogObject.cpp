// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "CatOrDogObject.h"

#include "graphqlservice/internal/Schema.h"

#include "graphqlservice/introspection/IntrospectionSchema.h"

using namespace std::literals;

namespace graphql::validation {
namespace object {

CatOrDog::CatOrDog(std::unique_ptr<const Concept>&& pimpl) noexcept
	: service::Object { pimpl->getTypeNames(), pimpl->getResolvers() }
	, _pimpl { std::move(pimpl) }
{
}

void CatOrDog::beginSelectionSet(const service::SelectionSetParams& params) const
{
	_pimpl->beginSelectionSet(params);
}

void CatOrDog::endSelectionSet(const service::SelectionSetParams& params) const
{
	_pimpl->endSelectionSet(params);
}

} // namespace object

void AddCatOrDogDetails(const std::shared_ptr<schema::UnionType>& typeCatOrDog, const std::shared_ptr<schema::Schema>& schema)
{
	typeCatOrDog->AddPossibleTypes({
		schema->LookupType(R"gql(Cat)gql"sv),
		schema->LookupType(R"gql(Dog)gql"sv)
	});
}

} // namespace graphql::validation
