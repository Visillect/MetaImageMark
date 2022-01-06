add_executable(bench_lin_transform_minimg minimg.cpp)
target_link_libraries(bench_lin_transform_minimg PRIVATE benchmark_tools benchmarks)

if (${OpenCV_FOUND})
    add_executable(bench_lin_transform_opencv opencv.cpp)
    target_link_libraries(bench_lin_transform_opencv PRIVATE benchmark_tools "${OpenCV_LIBS}" benchmarks)
endif ()
