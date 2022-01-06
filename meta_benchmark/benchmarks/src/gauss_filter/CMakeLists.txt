add_executable(bench_gauss_minimg minimg.cpp)
target_link_libraries(bench_gauss_minimg PRIVATE benchmark_tools benchmarks)

if (${OpenCV_FOUND})
    add_executable(bench_gauss_opencv opencv.cpp)
    target_link_libraries(bench_gauss_opencv PRIVATE benchmark_tools "${OpenCV_LIBS}" benchmarks)
endif ()
