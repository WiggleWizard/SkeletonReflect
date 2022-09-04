#include "SkeletonReflect/SourceFile.h"

#include "SkeletonReflect/Scanner.h"

#include <iostream>
#include <sstream>
#include <fstream>


NAMESPACE_BEGIN(SkeletonReflect)

SourceFile::SourceFile(const eastl::string& filepath)
	: _filepath(filepath)
{
	// Read full file into memory
	std::ifstream fin(filepath.c_str());

	std::stringstream buffer;
	buffer << fin.rdbuf();

	_scanner = eastl::make_shared<Scanner>(buffer.str().c_str());
}

void SourceFile::ScanTokens()
{
	_scanner->ScanTokens();
}

NAMESPACE_END