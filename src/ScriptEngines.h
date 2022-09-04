#pragma once

#include "CommonDefs.h"

#include "SkeletonReflect/ScriptEngine.h"
#include "ScriptEngineWren.h"

#include <EASTL/map.h>
#include <EASTL/functional.h>


NAMESPACE_BEGIN(SkeletonReflect)

static ea::map<ea::string, ea::function<ea::shared_ptr<ScriptEngine>()>> availableScriptEngines =
{
	{"wren", [] { return ea::make_shared<ScriptEngineWren>(); }},
};

static ea::string listAvailableEngines()
{
	ea::string result = "";
	for(const auto& scriptEngineEntry : availableScriptEngines)
	{
		result += scriptEngineEntry.first;
	}
	return result;
}

NAMESPACE_END