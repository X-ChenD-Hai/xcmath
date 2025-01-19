enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_vec vec.cc)
target_link_libraries(test_vec xcmath ${GTEST_BOTH_LIBRARIES})
add_executable(test_mat mat.cc)
target_link_libraries(test_mat xcmath ${GTEST_BOTH_LIBRARIES})

add_test(NAME all COMMAND test_mat&&test_vec)

# message(FATAL_ERROR ${CMAKE_CURRENT_BINARY_DIR}/test_xcmath)