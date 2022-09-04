embed_resources(PROJECT_RESOURCES
    CodeGenerator.wren)

add_executable(${PROJECT_NAME}
    "SkeletonReflectApp.cpp"
    "EASTLMem.cpp"
    
    "Scanner.cpp"
    "SourceFile.cpp"
    "SourceVisitor.cpp"
    "CodeGeneratorScriptable.cpp"

    # Script engines
    "ScriptEngineWren.cpp"

    ${PROJECT_RESOURCES})

include_directories(
    "."
    "${CMAKE_SOURCE_DIR}/include"
    "${PROJECT_RESOURCES_INCLUDE_DIR}")

target_link_libraries(${PROJECT_NAME}
    EASTL
    spdlog
    Wren
    SkeletonMinRes
    argparse)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
add_custom_target(NatVis SOURCES ${CMAKE_SOURCE_DIR}/thirdparty/EASTL/repo/doc/EASTL.natvis)