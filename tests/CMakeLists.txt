find_package(glm CONFIG REQUIRED)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_vec vec.cc)
target_link_libraries(test_vec xcmath ${GTEST_BOTH_LIBRARIES})
add_executable(test_mat mat.cc)
target_link_libraries(test_mat xcmath ${GTEST_BOTH_LIBRARIES})
add_executable(test_utils utils.cc)
target_link_libraries(test_utils xcmath ${GTEST_BOTH_LIBRARIES})
add_executable(test_function function.cc)
target_link_libraries(test_function xcmath ${GTEST_BOTH_LIBRARIES})


add_executable(test_graphics graphics.cc)
target_link_libraries(test_graphics PRIVATE xcmath glm::glm ${GTEST_BOTH_LIBRARIES})

# message(FATAL_ERROR ${CMAKE_CURRENT_BINARY_DIR}/test_xcmath)
add_test(NAME mat COMMAND test_mat)
add_test(NAME vec COMMAND test_vec)
add_test(NAME utils COMMAND test_utils)
add_test(NAME graphics COMMAND test_graphics)
add_test(NAME function COMMAND test_function)