#pragma once

#include "CommonDefs.h"

#include <EASTL/shared_ptr.h>
#include <EASTL/string.h>
#include <EASTL/vector.h>
#include <EASTL/chrono.h>

#include <filesystem>


NAMESPACE_BEGIN(SkeletonReflect)

class SourceFile;

class SourceVisitor
{
public:

	SourceVisitor(const eastl::string& rootPath)
		: _rootPath(rootPath)
	{}

	// Begin scanning at the root
	void Scan(bool bRecursive = true);
	bool HasBeenScanned() const;

	eastl::vector<eastl::shared_ptr<SourceFile>>& GetSourceFiles() { return _sourceFiles; }

private:

	void Scan(bool bRecursive, const std::filesystem::path& dirPath);

	eastl::chrono::time_point<eastl::chrono::system_clock> _lastVisit;
	eastl::string _rootPath{};
	eastl::vector<eastl::shared_ptr<SourceFile>> _sourceFiles{};
};

NAMESPACE_END