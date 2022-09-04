#pragma once

#include "CommonDefs.h"

#include <EASTL/hash_map.h>
#include <EASTL/string.h>


NAMESPACE_BEGIN(SkeletonReflect)

class ScriptEngine
{
public:
	virtual void Initialize() = 0;

	/**
	 * \brief Gets the full program script
	 */
	virtual ea::string GetFullScript() const = 0;

	/**
	 * \brief Called when application first attempts to scan
	 */
	virtual ea::hash_map<ea::string, int> GetUserDefinedTokenTypes() = 0;
};

NAMESPACE_END