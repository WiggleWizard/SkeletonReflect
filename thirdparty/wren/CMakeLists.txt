  file(GLOB_RECURSE WREN_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/repo/src/vm/*.c)

  add_library(Wren STATIC ${WREN_SOURCES})
  target_compile_definitions(Wren PRIVATE WREN_OPT_META=0 WREN_OPT_RANDOM=0)
  target_include_directories(Wren PUBLIC "${CMAKE_CURRENT_LIST_DIR}/repo/src/include")

  #set_target_properties(Wren PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${WREN_INCLUDE_DIR})