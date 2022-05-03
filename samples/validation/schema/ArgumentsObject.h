// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef ARGUMENTSOBJECT_H
#define ARGUMENTSOBJECT_H

#include "ValidationSchema.h"

namespace graphql::validation::object {
namespace methods::ArgumentsHas {

template <class TImpl>
concept getMultipleReqsWithParams = requires (TImpl impl, service::FieldParams params, int xArg, int yArg)
{
	{ service::AwaitableScalar<int> { impl.getMultipleReqs(std::move(params), std::move(xArg), std::move(yArg)) } };
};

template <class TImpl>
concept getMultipleReqs = requires (TImpl impl, int xArg, int yArg)
{
	{ service::AwaitableScalar<int> { impl.getMultipleReqs(std::move(xArg), std::move(yArg)) } };
};

template <class TImpl>
concept getBooleanArgFieldWithParams = requires (TImpl impl, service::FieldParams params, std::optional<bool> booleanArgArg)
{
	{ service::AwaitableScalar<std::optional<bool>> { impl.getBooleanArgField(std::move(params), std::move(booleanArgArg)) } };
};

template <class TImpl>
concept getBooleanArgField = requires (TImpl impl, std::optional<bool> booleanArgArg)
{
	{ service::AwaitableScalar<std::optional<bool>> { impl.getBooleanArgField(std::move(booleanArgArg)) } };
};

template <class TImpl>
concept getFloatArgFieldWithParams = requires (TImpl impl, service::FieldParams params, std::optional<double> floatArgArg)
{
	{ service::AwaitableScalar<std::optional<double>> { impl.getFloatArgField(std::move(params), std::move(floatArgArg)) } };
};

template <class TImpl>
concept getFloatArgField = requires (TImpl impl, std::optional<double> floatArgArg)
{
	{ service::AwaitableScalar<std::optional<double>> { impl.getFloatArgField(std::move(floatArgArg)) } };
};

template <class TImpl>
concept getIntArgFieldWithParams = requires (TImpl impl, service::FieldParams params, std::optional<int> intArgArg)
{
	{ service::AwaitableScalar<std::optional<int>> { impl.getIntArgField(std::move(params), std::move(intArgArg)) } };
};

template <class TImpl>
concept getIntArgField = requires (TImpl impl, std::optional<int> intArgArg)
{
	{ service::AwaitableScalar<std::optional<int>> { impl.getIntArgField(std::move(intArgArg)) } };
};

template <class TImpl>
concept getNonNullBooleanArgFieldWithParams = requires (TImpl impl, service::FieldParams params, bool nonNullBooleanArgArg)
{
	{ service::AwaitableScalar<bool> { impl.getNonNullBooleanArgField(std::move(params), std::move(nonNullBooleanArgArg)) } };
};

template <class TImpl>
concept getNonNullBooleanArgField = requires (TImpl impl, bool nonNullBooleanArgArg)
{
	{ service::AwaitableScalar<bool> { impl.getNonNullBooleanArgField(std::move(nonNullBooleanArgArg)) } };
};

template <class TImpl>
concept getNonNullBooleanListFieldWithParams = requires (TImpl impl, service::FieldParams params, std::optional<std::vector<bool>> nonNullBooleanListArgArg)
{
	{ service::AwaitableScalar<std::optional<std::vector<bool>>> { impl.getNonNullBooleanListField(std::move(params), std::move(nonNullBooleanListArgArg)) } };
};

template <class TImpl>
concept getNonNullBooleanListField = requires (TImpl impl, std::optional<std::vector<bool>> nonNullBooleanListArgArg)
{
	{ service::AwaitableScalar<std::optional<std::vector<bool>>> { impl.getNonNullBooleanListField(std::move(nonNullBooleanListArgArg)) } };
};

template <class TImpl>
concept getBooleanListArgFieldWithParams = requires (TImpl impl, service::FieldParams params, std::vector<std::optional<bool>> booleanListArgArg)
{
	{ service::AwaitableScalar<std::optional<std::vector<std::optional<bool>>>> { impl.getBooleanListArgField(std::move(params), std::move(booleanListArgArg)) } };
};

template <class TImpl>
concept getBooleanListArgField = requires (TImpl impl, std::vector<std::optional<bool>> booleanListArgArg)
{
	{ service::AwaitableScalar<std::optional<std::vector<std::optional<bool>>>> { impl.getBooleanListArgField(std::move(booleanListArgArg)) } };
};

template <class TImpl>
concept getOptionalNonNullBooleanArgFieldWithParams = requires (TImpl impl, service::FieldParams params, bool optionalBooleanArgArg)
{
	{ service::AwaitableScalar<bool> { impl.getOptionalNonNullBooleanArgField(std::move(params), std::move(optionalBooleanArgArg)) } };
};

template <class TImpl>
concept getOptionalNonNullBooleanArgField = requires (TImpl impl, bool optionalBooleanArgArg)
{
	{ service::AwaitableScalar<bool> { impl.getOptionalNonNullBooleanArgField(std::move(optionalBooleanArgArg)) } };
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

} // namespace methods::ArgumentsHas

class [[nodiscard]] Arguments final
	: public service::Object
{
private:
	[[nodiscard]] service::AwaitableResolver resolveMultipleReqs(service::ResolverParams&& params) const;
	[[nodiscard]] service::AwaitableResolver resolveBooleanArgField(service::ResolverParams&& params) const;
	[[nodiscard]] service::AwaitableResolver resolveFloatArgField(service::ResolverParams&& params) const;
	[[nodiscard]] service::AwaitableResolver resolveIntArgField(service::ResolverParams&& params) const;
	[[nodiscard]] service::AwaitableResolver resolveNonNullBooleanArgField(service::ResolverParams&& params) const;
	[[nodiscard]] service::AwaitableResolver resolveNonNullBooleanListField(service::ResolverParams&& params) const;
	[[nodiscard]] service::AwaitableResolver resolveBooleanListArgField(service::ResolverParams&& params) const;
	[[nodiscard]] service::AwaitableResolver resolveOptionalNonNullBooleanArgField(service::ResolverParams&& params) const;

	[[nodiscard]] service::AwaitableResolver resolve_typename(service::ResolverParams&& params) const;

	struct [[nodiscard]] Concept
	{
		virtual ~Concept() = default;

		virtual void beginSelectionSet(const service::SelectionSetParams& params) const = 0;
		virtual void endSelectionSet(const service::SelectionSetParams& params) const = 0;

		[[nodiscard]] virtual service::AwaitableScalar<int> getMultipleReqs(service::FieldParams&& params, int&& xArg, int&& yArg) const = 0;
		[[nodiscard]] virtual service::AwaitableScalar<std::optional<bool>> getBooleanArgField(service::FieldParams&& params, std::optional<bool>&& booleanArgArg) const = 0;
		[[nodiscard]] virtual service::AwaitableScalar<std::optional<double>> getFloatArgField(service::FieldParams&& params, std::optional<double>&& floatArgArg) const = 0;
		[[nodiscard]] virtual service::AwaitableScalar<std::optional<int>> getIntArgField(service::FieldParams&& params, std::optional<int>&& intArgArg) const = 0;
		[[nodiscard]] virtual service::AwaitableScalar<bool> getNonNullBooleanArgField(service::FieldParams&& params, bool&& nonNullBooleanArgArg) const = 0;
		[[nodiscard]] virtual service::AwaitableScalar<std::optional<std::vector<bool>>> getNonNullBooleanListField(service::FieldParams&& params, std::optional<std::vector<bool>>&& nonNullBooleanListArgArg) const = 0;
		[[nodiscard]] virtual service::AwaitableScalar<std::optional<std::vector<std::optional<bool>>>> getBooleanListArgField(service::FieldParams&& params, std::vector<std::optional<bool>>&& booleanListArgArg) const = 0;
		[[nodiscard]] virtual service::AwaitableScalar<bool> getOptionalNonNullBooleanArgField(service::FieldParams&& params, bool&& optionalBooleanArgArg) const = 0;
	};

	template <class T>
	struct [[nodiscard]] Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		[[nodiscard]] service::AwaitableScalar<int> getMultipleReqs(service::FieldParams&& params, int&& xArg, int&& yArg) const final
		{
			if constexpr (methods::ArgumentsHas::getMultipleReqsWithParams<T>)
			{
				return { _pimpl->getMultipleReqs(std::move(params), std::move(xArg), std::move(yArg)) };
			}
			else if constexpr (methods::ArgumentsHas::getMultipleReqs<T>)
			{
				return { _pimpl->getMultipleReqs(std::move(xArg), std::move(yArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Arguments::getMultipleReqs is not implemented)ex");
			}
		}

		[[nodiscard]] service::AwaitableScalar<std::optional<bool>> getBooleanArgField(service::FieldParams&& params, std::optional<bool>&& booleanArgArg) const final
		{
			if constexpr (methods::ArgumentsHas::getBooleanArgFieldWithParams<T>)
			{
				return { _pimpl->getBooleanArgField(std::move(params), std::move(booleanArgArg)) };
			}
			else if constexpr (methods::ArgumentsHas::getBooleanArgField<T>)
			{
				return { _pimpl->getBooleanArgField(std::move(booleanArgArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Arguments::getBooleanArgField is not implemented)ex");
			}
		}

		[[nodiscard]] service::AwaitableScalar<std::optional<double>> getFloatArgField(service::FieldParams&& params, std::optional<double>&& floatArgArg) const final
		{
			if constexpr (methods::ArgumentsHas::getFloatArgFieldWithParams<T>)
			{
				return { _pimpl->getFloatArgField(std::move(params), std::move(floatArgArg)) };
			}
			else if constexpr (methods::ArgumentsHas::getFloatArgField<T>)
			{
				return { _pimpl->getFloatArgField(std::move(floatArgArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Arguments::getFloatArgField is not implemented)ex");
			}
		}

		[[nodiscard]] service::AwaitableScalar<std::optional<int>> getIntArgField(service::FieldParams&& params, std::optional<int>&& intArgArg) const final
		{
			if constexpr (methods::ArgumentsHas::getIntArgFieldWithParams<T>)
			{
				return { _pimpl->getIntArgField(std::move(params), std::move(intArgArg)) };
			}
			else if constexpr (methods::ArgumentsHas::getIntArgField<T>)
			{
				return { _pimpl->getIntArgField(std::move(intArgArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Arguments::getIntArgField is not implemented)ex");
			}
		}

		[[nodiscard]] service::AwaitableScalar<bool> getNonNullBooleanArgField(service::FieldParams&& params, bool&& nonNullBooleanArgArg) const final
		{
			if constexpr (methods::ArgumentsHas::getNonNullBooleanArgFieldWithParams<T>)
			{
				return { _pimpl->getNonNullBooleanArgField(std::move(params), std::move(nonNullBooleanArgArg)) };
			}
			else if constexpr (methods::ArgumentsHas::getNonNullBooleanArgField<T>)
			{
				return { _pimpl->getNonNullBooleanArgField(std::move(nonNullBooleanArgArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Arguments::getNonNullBooleanArgField is not implemented)ex");
			}
		}

		[[nodiscard]] service::AwaitableScalar<std::optional<std::vector<bool>>> getNonNullBooleanListField(service::FieldParams&& params, std::optional<std::vector<bool>>&& nonNullBooleanListArgArg) const final
		{
			if constexpr (methods::ArgumentsHas::getNonNullBooleanListFieldWithParams<T>)
			{
				return { _pimpl->getNonNullBooleanListField(std::move(params), std::move(nonNullBooleanListArgArg)) };
			}
			else if constexpr (methods::ArgumentsHas::getNonNullBooleanListField<T>)
			{
				return { _pimpl->getNonNullBooleanListField(std::move(nonNullBooleanListArgArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Arguments::getNonNullBooleanListField is not implemented)ex");
			}
		}

		[[nodiscard]] service::AwaitableScalar<std::optional<std::vector<std::optional<bool>>>> getBooleanListArgField(service::FieldParams&& params, std::vector<std::optional<bool>>&& booleanListArgArg) const final
		{
			if constexpr (methods::ArgumentsHas::getBooleanListArgFieldWithParams<T>)
			{
				return { _pimpl->getBooleanListArgField(std::move(params), std::move(booleanListArgArg)) };
			}
			else if constexpr (methods::ArgumentsHas::getBooleanListArgField<T>)
			{
				return { _pimpl->getBooleanListArgField(std::move(booleanListArgArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Arguments::getBooleanListArgField is not implemented)ex");
			}
		}

		[[nodiscard]] service::AwaitableScalar<bool> getOptionalNonNullBooleanArgField(service::FieldParams&& params, bool&& optionalBooleanArgArg) const final
		{
			if constexpr (methods::ArgumentsHas::getOptionalNonNullBooleanArgFieldWithParams<T>)
			{
				return { _pimpl->getOptionalNonNullBooleanArgField(std::move(params), std::move(optionalBooleanArgArg)) };
			}
			else if constexpr (methods::ArgumentsHas::getOptionalNonNullBooleanArgField<T>)
			{
				return { _pimpl->getOptionalNonNullBooleanArgField(std::move(optionalBooleanArgArg)) };
			}
			else
			{
				throw std::runtime_error(R"ex(Arguments::getOptionalNonNullBooleanArgField is not implemented)ex");
			}
		}

		void beginSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::ArgumentsHas::beginSelectionSet<T>)
			{
				_pimpl->beginSelectionSet(params);
			}
		}

		void endSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::ArgumentsHas::endSelectionSet<T>)
			{
				_pimpl->endSelectionSet(params);
			}
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Arguments(std::unique_ptr<const Concept>&& pimpl) noexcept;

	[[nodiscard]] service::TypeNames getTypeNames() const noexcept;
	[[nodiscard]] service::ResolverMap getResolvers() const noexcept;

	void beginSelectionSet(const service::SelectionSetParams& params) const final;
	void endSelectionSet(const service::SelectionSetParams& params) const final;

	const std::unique_ptr<const Concept> _pimpl;

public:
	template <class T>
	Arguments(std::shared_ptr<T> pimpl) noexcept
		: Arguments { std::unique_ptr<const Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	[[nodiscard]] static constexpr std::string_view getObjectType() noexcept
	{
		return { R"gql(Arguments)gql" };
	}
};

} // namespace graphql::validation::object

#endif // ARGUMENTSOBJECT_H
