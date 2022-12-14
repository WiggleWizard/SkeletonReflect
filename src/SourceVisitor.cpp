#include "SkeletonReflect/SourceVisitor.h"

#include "SkeletonReflect/SourceFile.h"

namespace fs = std::filesystem;


NAMESPACE_BEGIN(SkeletonReflect)

void SourceVisitor::Scan(bool bRecursive)
{
	Scan(bRecursive, _rootPath.c_str());
	_lastVisit = eastl::chrono::system_clock::now();
}

bool SourceVisitor::HasBeenScanned() const
{
	return _lastVisit > eastl::chrono::time_point<eastl::chrono::system_clock>();
}

void SourceVisitor::Scan(bool bRecursive, const std::filesystem::path& dirPath)
{
	for(const auto& dir : fs::directory_iterator(dirPath))
	{
		if(bRecursive && dir.is_directory())
		{
			Scan(bRecursive, dir.path());
			continue;
		}

		eastl::string filePath = dir.path().string().c_str();
		eastl::string fileExt  = filePath.substr(filePath.find_last_of(".") + 1);

		// Is this file a header file
		if(fileExt != "h" && fileExt != "hpp")
		{
			continue;
		}

		eastl::shared_ptr<SourceFile> newSourceFile = eastl::make_shared<SourceFile>(filePath);
		_sourceFiles.push_back(newSourceFile);

		newSourceFile->ScanTokens();
	}
}

NAMESPACE_END