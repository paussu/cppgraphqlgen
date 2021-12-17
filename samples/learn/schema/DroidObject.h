// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef DROIDOBJECT_H
#define DROIDOBJECT_H

#include "StarWarsSchema.h"

namespace graphql::learn::object {

class Droid
	: public service::Object
	, public Character
{
protected:
	explicit Droid();

public:
	virtual service::FieldResult<std::optional<response::StringType>> getPrimaryFunction(service::FieldParams&& params) const = 0;

private:
	std::future<service::ResolverResult> resolveId(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveName(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveFriends(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveAppearsIn(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolvePrimaryFunction(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

} // namespace graphql::learn::object

#endif // DROIDOBJECT_H
