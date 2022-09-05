file(GLOB_RECURSE WREN_SOURCES ${wren_SOURCE_DIR}/src/vm/*.c)

add_library(Wren STATIC ${WREN_SOURCES})
target_compile_definitions(Wren PRIVATE WREN_OPT_META=0 WREN_OPT_RANDOM=0)
target_include_directories(Wren PUBLIC "${wren_SOURCE_DIR}/src/include")