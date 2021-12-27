add_executable(bench_example3 main.cpp)
target_link_libraries(bench_example3 PRIVATE benchmark_tools)
target_include_directories(bench_example3 PRIVATE ../../benchmarks/include)
