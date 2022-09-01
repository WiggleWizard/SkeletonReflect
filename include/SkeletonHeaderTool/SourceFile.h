#pragma once

#include "Scanner.h"

#include <EASTL/string.h>


class SourceFile
{
public:

	SourceFile(const eastl::string& filepath);
	void ScanTokens();

private:

	eastl::string _filepath;
	Scanner _scanner;
};