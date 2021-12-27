find_package(OpenCV)

if (${OpenCV_FOUND})
    add_executable(bench_example4 main.cpp)
    target_link_libraries(bench_example4 PRIVATE benchmark_tools "${OpenCV_LIBS}")
    target_include_directories(bench_example4 PRIVATE ../../benchmarks/include)
endif ()
