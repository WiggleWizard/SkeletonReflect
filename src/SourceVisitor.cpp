#include "SkeletonHeaderTool/SourceVisitor.h"

#include "SkeletonHeaderTool/SourceFile.h"

namespace fs = std::filesystem;


void SourceVisitor::Scan(bool bRecursive)
{
	Scan(bRecursive, _rootPath.c_str());
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

		_sourceFiles.push_back({ filePath });
		SourceFile& newSourceFile = _sourceFiles[_sourceFiles.size() - 1];

		newSourceFile.ScanTokens();
	}
}
