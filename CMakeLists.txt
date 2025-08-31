cmake_minimum_required(VERSION 3.15)
project(xcmath LANGUAGES CXX C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
option(BUILD_TESTING "Build tests" ON)
option(XCMATH_BUILD_SHARED_LIBS "Build dynamic library" OFF)
add_subdirectory(xcmath)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()


install(TARGETS xcmath EXPORT xcmath)
install(TARGETS xcmath_symbool_system EXPORT symbool_system)

install(
    EXPORT xcmath
    NAMESPACE xcmath::
    FILE xcmathConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/xcmath
)
install(
    DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/xcmath/mobject
    ${CMAKE_CURRENT_SOURCE_DIR}/xcmath/utils
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xcmath
)
install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/xcmath/xcmath.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xcmath
)
