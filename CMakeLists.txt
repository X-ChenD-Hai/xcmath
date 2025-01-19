cmake_minimum_required(VERSION 3.10)
project(math LANGUAGES CXX C)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)



add_subdirectory(src)
set(xcmath_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(test test/test1.cc)
target_include_directories(test PRIVATE ${math_INCLUDE_DIRS})
