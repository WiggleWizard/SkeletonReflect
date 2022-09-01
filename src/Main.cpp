#include "SkeletonHeaderTool/SourceVisitor.h"

#include <spdlog/spdlog.h>
#include <EASTL/string.h>

#include "SkeletonHeaderTool/Logging.h"
LOG_DECL(logger, Main);


int main(int argc, char *argv[])
{
	SourceVisitor visitor("tests");
	visitor.Scan();
}