cmake_minimum_required(VERSION 3.10)
project(math LANGUAGES CXX C)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
option(BUILD_TESTING "Build tests" ON)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
