set(xcmath_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
add_library(xcmath INTERFACE)
target_include_directories(xcmath INTERFACE ${xcmath_INCLUDE_DIRS})