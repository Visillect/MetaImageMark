add_executable(bench_box_filter_minimg minimg.cpp)
target_link_libraries(bench_box_filter_minimg PRIVATE benchmark_tools benchmarks)

if (${OpenCV_FOUND})
    add_executable(bench_box_filter_opencv opencv.cpp)
    target_link_libraries(bench_box_filter_opencv PRIVATE benchmark_tools "${OpenCV_LIBS}" benchmarks)
endif ()
