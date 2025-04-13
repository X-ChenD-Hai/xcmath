set(math_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
add_library(xcmath INTERFACE)
target_include_directories(xcmath INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}>
)
add_library(xcmath::xcnath ALIAS xcmath)

add_subdirectory(symbolsystem)