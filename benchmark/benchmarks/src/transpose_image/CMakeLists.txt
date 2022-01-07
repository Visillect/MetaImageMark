add_executable(bench_transpose_minimg minimg.cpp)
target_link_libraries(bench_transpose_minimg PRIVATE benchmark_tools benchmarks)

if (${OpenCV_FOUND})
    add_executable(bench_transpose_opencv opencv.cpp)
    target_link_libraries(bench_transpose_opencv PRIVATE benchmark_tools "${OpenCV_LIBS}" benchmarks)
endif ()
