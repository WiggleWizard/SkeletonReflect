#pragma once

#include <EASTL/shared_ptr.h>
#include <EASTL/string.h>

#include "CommonDefs.h"

// Forward decl to avoid polluting global namespace when this header file is included
namespace argparse
{
	class ArgumentParser;
}


NAMESPACE_BEGIN(SkeletonReflect)

class ScriptEngine;

/**
 * \brief Enum for choosing how logs are formatted
 *
 * ALF_RAW:             Completely raw and unformatted
 * ALF_TIMESTAMPED:     Uses spdlog's default output
 */
enum ApplicationLogFormat
{
	ALF_RAW,
	ALF_TIMESTAMPED
};

/**
 * \brief Contains application specific configuration variables
 */
struct ApplicationConfig
{
	ApplicationLogFormat stdoutFormat = ALF_RAW;

	ea::string scriptEngine = "wren";
	ea::string scriptPath   = "";
};

/**
 * \brief SkeletonReflect singleton application class. Call `Instance()` to get an instance
 */
 class Application
{
	Application() {}

public:
	static Application& Instance()
	{
		static Application instance;
		return instance;
	}

public:
	/**
	 * \brief Called from `int main(int argc, char* argv[])`
	 */
	int Main(int argCount, char* args[]);

	/**
	 * \brief Prints the usage of the application to stdout
	 */
	void PrintUsage() const;

	int ConfigureFromArgs(int argCount, char* args[]);

	ApplicationConfig& GetConfig();
	ea::shared_ptr<ScriptEngine> GetScriptEngine() const;

private:
	void SetupArgParser();

private:
	ApplicationConfig _config{};
	ea::shared_ptr<argparse::ArgumentParser> _argParser = nullptr;
	ea::shared_ptr<ScriptEngine> _scriptEngine = nullptr;
};

NAMESPACE_END