#pragma once

#include "CommonDefs.h"

#include "CodeGeneratorBase.h"

class WrenVM;


NAMESPACE_BEGIN(SkeletonReflect)

class SourceFile;

class CodeGeneratorScriptable : public CodeGeneratorBase
{
public:
	CodeGeneratorScriptable(eastl::shared_ptr<SourceVisitor> sourceVisitor, const eastl::string& outputDir);
	~CodeGeneratorScriptable();

	virtual void GenerateCode() override;
	virtual void GenerateCodeFromSourceFile(eastl::shared_ptr<SourceFile> sourceFile);
};

NAMESPACE_END