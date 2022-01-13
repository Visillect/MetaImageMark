project(opencv_benchmark)

find_package(OpenCV REQUIRED)

add_library(bench_opencv_base INTERFACE)
target_include_directories(bench_opencv_base INTERFACE include)
target_link_libraries(bench_opencv_base INTERFACE grid_benchmark
        opencv_core opencv_imgproc)

add_executable(bench_opencv_merge src/merge.cpp)
target_link_libraries(bench_opencv_merge PRIVATE bench_opencv_base)
