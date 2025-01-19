enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE TEST_SOURCES "*.cc")

add_executable(test_xcmath ${TEST_SOURCES})
target_link_libraries(test_xcmath xcmath ${GTEST_BOTH_LIBRARIES})