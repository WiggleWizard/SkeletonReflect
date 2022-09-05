#include "ScriptEngineWren.h"

#include "SkeletonReflectApp.h"
#include "SkeletonReflect/TokenType.h"
#include "SkeletonMinRes/Loader.h"

#include <wren.hpp>

#include "SkeletonReflect/Logging.h"
LOGGER(logger, ScriptEngineWren);
LOGGER(wrenLogger, WrenScript);


NAMESPACE_BEGIN(SkeletonReflect)

void WrenWriteFunc(WrenVM* vm, const char* text)
{
	wrenLogger->info("[Script] {}", text);
}

void WrenErrorFunc(WrenVM* vm, WrenErrorType errorType, const char* module, const int line, const char* msg)
{
	switch(errorType)
	{
	case WREN_ERROR_COMPILE:
	{
		wrenLogger->error("[Compile] [{}@L{}] {}", module, line, msg);
	} break;
	case WREN_ERROR_STACK_TRACE:
	{
		wrenLogger->error("[Stack] [{}@L{}] in {}", module, line, msg);
	} break;
	case WREN_ERROR_RUNTIME:
	{
		wrenLogger->error("[Runtime] {}", msg);
	} break;
	}
}

ScriptEngineWren::~ScriptEngineWren()
{
	if(_wrenVm)
	{
		wrenFreeVM(_wrenVm);
	}
}

void ScriptEngineWren::Initialize()
{
	WrenConfiguration config;
	wrenInitConfiguration(&config);
	config.writeFn = &WrenWriteFunc;
	config.errorFn = &WrenErrorFunc;

	_wrenVm = wrenNewVM(&config);

	logger->info("Wren VM started");

	const ea::string fullScript = GetFullScript();

	// Attempt to "execute" the script
	if(wrenInterpret(_wrenVm, "main", fullScript.c_str()) != WREN_RESULT_SUCCESS)
	{
		logger->error("An error occurred during compilation or runtime of Wren script. Returning");
		return;
	}

	_wrenFnGetCustomKeywords = wrenMakeCallHandle(_wrenVm, "getCustomKeywords()");

	// Load the class into slot 0.
	wrenEnsureSlots(_wrenVm, 1);
	wrenGetVariable(_wrenVm, "main", "SkeletonReflect", 0);
	_wrenClassSkeletonReflect = wrenGetSlotHandle(_wrenVm, 0);
}

ea::string ScriptEngineWren::GetFullScript() const
{
	ea::string finalScript =  "// === HEADER GENERATED BY SKELETONREFLECT ===========\n";
	           finalScript += "// === DO NOT INCLUDE IN CUSTOM SCRIPTS\n";

	// Generate some Wren script that contains a the token types
	for(const auto& element : StringToTokenTypeMap)
	{
		finalScript += fmt::format("var TOK_{} = {}\n", element.first, element.second).c_str();
	}
	finalScript += "// ==================================================\n\n";

	// Ask the application for its config so we can figure out what script to load
	const ApplicationConfig& appConfig = Application::Instance().GetConfig();
	ea::string scriptStr = "";
	if(appConfig.scriptPath.empty())
	{
		// Load embedded script
		const SkeletonMinRes::Resource res = LOAD_RESOURCE(CodeGenerator_wren);
		scriptStr = res.Data();
	}

	// Construct final script string
	finalScript += scriptStr;

	return finalScript;
}

ea::hash_map<ea::string, int> ScriptEngineWren::GetUserDefinedTokenTypes()
{
	ea::hash_map<ea::string, int> customTokenTypes;

	wrenSetSlotHandle(_wrenVm, 0, _wrenClassSkeletonReflect);
	WrenInterpretResult r = wrenCall(_wrenVm, _wrenFnGetCustomKeywords);

	const int totalKeywordCount = wrenGetListCount(_wrenVm, 0);
	wrenEnsureSlots(_wrenVm, 4);
	for(int i = 0; i < totalKeywordCount; ++i)
	{
		wrenGetListElement(_wrenVm, 0, i, 1);
		if(wrenGetSlotType(_wrenVm, 1) == WREN_TYPE_MAP)
		{
			// Get the keyword
			wrenSetSlotString(_wrenVm, 2, "keyword");
			wrenGetMapValue(_wrenVm, 1, 2, 3);
			const ea::string keyword = wrenGetSlotString(_wrenVm, 3);

			// Get the ID
			wrenSetSlotString(_wrenVm, 2, "id");
			wrenGetMapValue(_wrenVm, 1, 2, 3);
			const int id = (int)wrenGetSlotDouble(_wrenVm, 3);

			// Amend the keyword + id
			customTokenTypes[keyword] = id;
		}
	}
	
	return customTokenTypes;
}

NAMESPACE_END
