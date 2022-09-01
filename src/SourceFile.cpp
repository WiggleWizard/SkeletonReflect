#include "SkeletonHeaderTool/SourceFile.h"

#include <iostream>
#include <sstream>
#include <fstream>


SourceFile::SourceFile(const eastl::string& filepath)
{
	// Read full file into memory
	std::ifstream fin(filepath.c_str());

	std::stringstream buffer;
	buffer << fin.rdbuf();

	_scanner.SetSource(buffer.str().c_str());
}

void SourceFile::ScanTokens()
{
	_scanner.ScanTokens();
}
