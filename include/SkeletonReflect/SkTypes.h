#pragma once

#include "CommonDefs.h"

#include <EASTL/vector.h>
#include <EASTL/string.h>


SK_NAMESPACE_BEGIN(Skeleton)

struct SkParam
{
	eastl::string name = "";
	eastl::string value = "";
};

typedef eastl::vector<SkParam> SkParams;

struct SkTypeBase
{
	eastl_size_t offset = eastl::string::npos;
	int lineNumber = -1;
	eastl::string uuid{};
	SkParams params{};
};

struct SkTypeProperty : public SkTypeBase
{
	eastl::string variableName{};
	eastl::string variableDisplayName{};
};

struct SkTypeFunctionParameter
{
	eastl::string paramName;
	//eastl::string paramType; // TODO
};

struct SkTypeFunction : public SkTypeBase
{
	eastl::string functionName{};
	eastl::vector<SkTypeFunctionParameter> parameters;
};

struct SkTypeClass : public SkTypeBase
{
	eastl::string className{};
	eastl::string classDisplayName{};

	eastl::vector<SkTypeProperty> properties;
	eastl::vector<SkTypeFunction> functions;
};

SK_NAMESPACE_END