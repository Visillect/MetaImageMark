project(grid_benchmark)

add_library(grid_benchmark src/grid_benchmark.cpp)

target_include_directories(grid_benchmark PUBLIC include)
target_link_libraries(grid_benchmark PUBLIC benchmark::benchmark system_info)

if (${ENABLE_TESTS})
    add_executable(test_grid src/test_grid_generator.cpp)
    target_link_libraries(test_grid PRIVATE grid_benchmark gtest_main)

    gtest_discover_tests(test_grid)

    add_executable(test_grid_benchmark src/test_grid_benchmark.cpp)
    target_link_libraries(test_grid_benchmark PRIVATE grid_benchmark)
endif ()
