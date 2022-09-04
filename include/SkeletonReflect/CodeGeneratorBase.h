#pragma once

#include "CommonDefs.h"

#include <EASTL/shared_ptr.h>
#include <EASTL/string.h>


NAMESPACE_BEGIN(SkeletonReflect)

class SourceVisitor;

class CodeGeneratorBase
{
public:
	CodeGeneratorBase(eastl::shared_ptr<SourceVisitor> sourceVisitor, const eastl::string& outputDir)
		: _sourceVisitor(sourceVisitor)
		, _outputDir(outputDir)
	{}

	virtual void GenerateCode() = 0;

protected:
	eastl::string _outputDir;
	eastl::shared_ptr<SourceVisitor> _sourceVisitor;
};

NAMESPACE_END