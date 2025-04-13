add_library(symbool_system SHARED)

target_compile_definitions(symbool_system PRIVATE -DXCMATH_EXPORTS)

file(GLOB_RECURSE SOURCES *.cc)

target_sources(symbool_system PRIVATE
    ${SOURCES}
)

add_library(xcmath::symbool_system ALIAS symbool_system)