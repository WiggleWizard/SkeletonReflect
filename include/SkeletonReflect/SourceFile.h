#pragma once

#include "CommonDefs.h"

#include <EASTL/string.h>
#include <EASTL/shared_ptr.h>


NAMESPACE_BEGIN(SkeletonReflect)

class Scanner;

class SourceFile
{
public:

	SourceFile(const eastl::string& filepath);
	void ScanTokens();

	eastl::string GetFilePath() const { return _filepath; }

private:

	eastl::string _filepath;
	eastl::shared_ptr<Scanner> _scanner = nullptr;
};

NAMESPACE_END