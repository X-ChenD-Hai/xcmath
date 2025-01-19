set(math_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
add_library(xcmath INTERFACE)
target_include_directories(xcmath INTERFACE ${math_INCLUDE_DIRS})