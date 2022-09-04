#pragma once

#include "CommonDefs.h"

#include <EASTL/hash_map.h>
#include <EASTL/string.h>


NAMESPACE_BEGIN(SkeletonReflect)

class ScriptEngine
{
public:
	virtual void Initialize() = 0;
	virtual ea::hash_map<ea::string, int> GetUserDefinedTokenTypes() = 0;
};

NAMESPACE_END