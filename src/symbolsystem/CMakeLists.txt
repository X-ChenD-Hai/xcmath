
if(XCMATH_BUILD_SHARED_LIBS)
    add_library(xcmath_symbool_system SHARED)
    target_compile_definitions(xcmath_symbool_system PRIVATE -DXCMATH_EXPORTS)
else()
    add_library(xcmath_symbool_system)
endif()

file(GLOB_RECURSE SOURCES *.cc)
file(GLOB_RECURSE symbol_system_HEADERS *.h *.hpp)

target_sources(xcmath_symbool_system PRIVATE
    ${SOURCES}
)


add_library(xcmath::symbol_system ALIAS xcmath_symbool_system)
install(FILES ${symbol_system_HEADERS}
    DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}/xcmath/symbolsystem)
