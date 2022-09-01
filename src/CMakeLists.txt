add_executable(${PROJECT_NAME}
    "Main.cpp"
    "EASTLMem.cpp"
    
    "Scanner.cpp"
    "SourceFile.cpp"
    "SourceVisitor.cpp")

include_directories(
    "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME}
    EASTL
    spdlog)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
add_custom_target(NatVis SOURCES ${CMAKE_SOURCE_DIR}/thirdparty/EASTL/repo/doc/EASTL.natvis "SourceVisitor.cpp")