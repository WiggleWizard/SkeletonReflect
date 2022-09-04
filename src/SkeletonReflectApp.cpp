#include "SkeletonReflectApp.h"

#include "SkeletonReflect/SourceVisitor.h"
#include "SkeletonReflect/CodeGeneratorScriptable.h"
#include "SkeletonReflect/ScriptEngine.h"
#include "ScriptEngines.h"

#include <spdlog/spdlog.h>
#include <EASTL/string.h>
#include <argparse/argparse.hpp>

#include <SkeletonMinRes/Loader.h>

#include "SkeletonReflect/Logging.h"
LOGGER(logger, Application);


NAMESPACE_BEGIN(SkeletonReflect)

int Application::Main(int argCount, char* args[])
{
	// Create script engine to make it available ASAP
	_scriptEngine = availableScriptEngines[_config.scriptEngine]();

	// Set up the arg parser first so we can then figure out any configuration things
	SetupArgParser();
	const int configureResult = ConfigureFromArgs(argCount, args);
	if(configureResult != 0)
	{
		return configureResult;
	}

	// Initialize the scripting engine
	_scriptEngine->Initialize();

	ea::shared_ptr<SourceVisitor> visitor = ea::make_shared<SourceVisitor>("tests");
	ea::shared_ptr<CodeGeneratorScriptable> codeGenerator = ea::make_shared<CodeGeneratorScriptable>(visitor, "out/tests/generated");
	codeGenerator->GenerateCode();

	return 0;
}

void Application::PrintUsage() const
{
}

int Application::ConfigureFromArgs(int argCount, char* args[])
{
	try
	{
		_argParser->parse_args(argCount, args);

		// Dump out script to stdout then exit
		if(_argParser->get<bool>("--dumpscript") == true)
		{
			printf("%s", _scriptEngine->GetFullScript().c_str());
			return -1;
		}

		// Set stdout log format
		if(_argParser->get<bool>("--standalone") == false)
		{
			spdlog::set_pattern("%v");
		}

		// Set the programming script file
		if(_argParser->is_used("--script"))
		{
			std::string arg = _argParser->get<std::string>("--script");

			_config.scriptPath = arg.c_str();
			logger->info("Using script {}", _config.scriptPath);
		}

		// Figure out which script engine to use
		ea::string scriptEngine = "wren";
		if(_argParser->is_used("--scriptengine"))
		{
			std::string arg = _argParser->get<std::string>("--scriptengine");
			ea::string requestedScriptEngine = arg.c_str();

			// If the requested scripting engine is not available, then alert and fall back to default
			if(availableScriptEngines.count(requestedScriptEngine) == 0)
			{
				logger->error("Script engine \"{}\" not available, defaulting to {}. Available scripting engines: {}", requestedScriptEngine, scriptEngine, listAvailableEngines());
			}
			else
			{
				scriptEngine = requestedScriptEngine;
			}
		}
		_config.scriptEngine = scriptEngine;
		logger->info("Using {} script engine", _config.scriptEngine);
	}
	catch(const std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
		std::cerr << *_argParser;
		return 1;
	}
	catch(const std::logic_error& err)
	{
		std::cerr << err.what() << std::endl;
		std::cerr << *_argParser;
		return 1;
	}

	return 0;
}

ApplicationConfig& Application::GetConfig()
{
	return _config;
}

ea::shared_ptr<ScriptEngine> Application::GetScriptEngine() const
{
	return _scriptEngine;
}

void Application::SetupArgParser()
{
	_argParser = ea::make_shared<argparse::ArgumentParser>("SkeletonReflect");
	if(!_argParser)
	{
		logger->critical("Arg parser failed to initialize correctly");
		return;
	}

	_argParser->add_argument("--standalone")
		.help("If enabled, will print all log lines with timestamps and categories")
		.default_value(false)
		.implicit_value(true)
		.nargs(0);

	_argParser->add_argument("--scriptengine")
		.help("Program scripting engine to use")
		.default_value(std::string{ "wren" })
		.nargs(1);

	_argParser->add_argument("--script")
		.help("Path to the programming script file. Will default to internal script files if not set")
		.default_value(std::string{""})
		.nargs(1);

	_argParser->add_argument("--dumpscript")
		.help("Dump script to terminal. Application will terminate after")
		.default_value(false)
		.implicit_value(true)
		.nargs(0);

	_argParser->add_argument("--inputdirs")
		.help("Path to the input directories (separated by semicolon) that will be recursively fed into SkeletonReflect")
		.default_value(std::string{ "" })
		.nargs(1);

	_argParser->add_argument("--outputdir")
		.help("")
		.default_value(std::string{ "" })
		.nargs(1);
}

NAMESPACE_END


// Initialize the application
int main(int argc, char* argv[])
{
	return skr::Application::Instance().Main(argc, argv);
}
