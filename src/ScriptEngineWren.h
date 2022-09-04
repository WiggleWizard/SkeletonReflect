#pragma once

#include "SkeletonReflect/ScriptEngine.h"

#include "CommonDefs.h"

#include <EASTL/shared_ptr.h>

class WrenVM;
class WrenHandle;


NAMESPACE_BEGIN(SkeletonReflect)

class ScriptEngineWren : public ScriptEngine
{
public:
	~ScriptEngineWren();

	void Initialize() override;
	ea::hash_map<ea::string, int> GetUserDefinedTokenTypes() override;

private:
	WrenVM* _wrenVm = nullptr;

	// Wren method store
	WrenHandle* _wrenClassSkeletonReflect = nullptr;
	WrenHandle* _wrenFnGetCustomKeywords = nullptr;
};

NAMESPACE_END