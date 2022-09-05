set(CPM_DOWNLOAD_VERSION 0.35.5) 
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake")
    file(DOWNLOAD https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

# Unfortunately, for both EABase and EASTL they include themselves recursively within their tests dir.
# So if one feeds CPM.cmake the Git URL, it will use `--recursive` which results in the build system hanging...
# So as a work around I've used direct reference ZIPs (since we don't need their tests).

# EABase
CPMAddPackage(
    NAME EABase
    URL "https://github.com/electronicarts/EABase/archive/521cb053d9320636f53226ffc616216cf532f0ef.zip"
    VERSION 521cb053d9320636f53226ffc616216cf532f0ef)

# EASTL
CPMAddPackage(
    NAME EASTL
    URL "https://github.com/electronicarts/EASTL/archive/5eb9b1ec09faaf5965125a07f3907a3d9cd0e1e7.zip"
    VERSION 5eb9b1ec09faaf5965125a07f3907a3d9cd0e1e7)

# spdlog
CPMAddPackage(
    NAME spdlog
    GITHUB_REPOSITORY gabime/spdlog
    VERSION 1.10.0)

# Wren
CPMAddPackage(
    NAME wren
    GITHUB_REPOSITORY wren-lang/wren
    GIT_TAG 0.4.0)
include("${CMAKE_SOURCE_DIR}/cmake/wren.cmake")

# SkeletonMinRes
CPMAddPackage(
    NAME SkeletonMinRes
    GITHUB_REPOSITORY WiggleWizard/SkeletonMinRes
    VERSION 1.0.0)

# argparse
CPMAddPackage(
    NAME argparse
    GITHUB_REPOSITORY p-ranav/argparse
    VERSION 2.6)