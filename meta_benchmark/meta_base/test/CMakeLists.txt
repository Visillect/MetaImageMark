enable_testing()

include(GoogleTest)

add_executable(test_grid test_grid.cpp)
target_link_libraries(test_grid PUBLIC meta_base gtest_main)

gtest_discover_tests(test_grid)
