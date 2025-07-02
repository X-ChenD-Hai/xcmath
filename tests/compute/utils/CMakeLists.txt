include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(test_memorypool memorypool.cc)
target_link_libraries(test_memorypool xcmath ${GTEST_BOTH_LIBRARIES})



add_test(NAME memorypool COMMAND test_memorypool)


