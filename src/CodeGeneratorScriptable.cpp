#include "SkeletonReflect/CodeGeneratorScriptable.h"

#include "SkeletonReflect/SourceVisitor.h"

#include "SkeletonReflect/Logging.h"
LOGGER(logger, CodeGeneratorScriptable);


NAMESPACE_BEGIN(SkeletonReflect)

CodeGeneratorScriptable::CodeGeneratorScriptable(eastl::shared_ptr<SourceVisitor> sourceVisitor, const eastl::string& outputDir)
	: CodeGeneratorBase(sourceVisitor, outputDir)
{
	
}

CodeGeneratorScriptable::~CodeGeneratorScriptable()
{
	
}

void CodeGeneratorScriptable::GenerateCode()
{
	if(!_sourceVisitor->HasBeenScanned())
	{
		_sourceVisitor->Scan();
	}

	// Iterate through all source files from the source visitor and attempt to generate sources for them
	for(const eastl::shared_ptr<SourceFile> sourceFile : _sourceVisitor->GetSourceFiles())
	{
		GenerateCodeFromSourceFile(sourceFile);
	}
}

void CodeGeneratorScriptable::GenerateCodeFromSourceFile(eastl::shared_ptr<SourceFile> sourceFile)
{

}

NAMESPACE_END