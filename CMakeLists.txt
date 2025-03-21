cmake_minimum_required(VERSION 3.15)
project(xcmath LANGUAGES CXX C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
add_subdirectory(src)
option(BUILD_TESTING "Build tests" ON)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

install(TARGETS xcmath EXPORT xcmath)

install(
    EXPORT xcmath
    NAMESPACE xcmath::
    FILE xcmathConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/xcmath
)
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/mobject ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xcmath
)
install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/xcmath.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xcmath
)