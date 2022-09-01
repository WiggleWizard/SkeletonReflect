#pragma once

#include <SkeletonHeaderTool/SourceFile.h>

#include <EASTL/string.h>
#include <EASTL/vector.h>

#include <filesystem>


class SourceVisitor
{
public:

	SourceVisitor(const eastl::string& rootPath)
		: _rootPath(rootPath)
	{}

	// Begin scanning at the root
	void Scan(bool bRecursive = true);

private:

	void Scan(bool bRecursive, const std::filesystem::path& dirPath);

	eastl::string _rootPath{};
	eastl::vector<SourceFile> _sourceFiles{};
};