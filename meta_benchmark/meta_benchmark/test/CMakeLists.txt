enable_testing()

include(GoogleTest)

add_executable(test_grid test_grid.cpp)
target_link_libraries(test_grid PRIVATE meta_benchmark gtest_main)

gtest_discover_tests(test_grid)

add_executable(test_meta_benchmark test_benchmark.cpp)
target_link_libraries(test_meta_benchmark PRIVATE meta_benchmark)
