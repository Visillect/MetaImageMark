project(opencv_benchmark)

find_package(OpenCV QUIET)

if (NOT OpenCV_FOUND)
    message(WARNING "OpenCV was not found. \
        Specify OpenCV_DIR to cmake configure file. \
        Disabling OpenCV benchmarks.")
else ()
    add_library(bench_opencv_base INTERFACE)
    target_include_directories(bench_opencv_base INTERFACE include)
    target_link_libraries(bench_opencv_base INTERFACE image_benchmark
            opencv_core opencv_imgproc)

    add_executable(bench_opencv_merge src/merge.cpp)
    target_link_libraries(bench_opencv_merge PRIVATE bench_opencv_base)

    add_executable(bench_opencv_transpose src/transpose.cpp)
    target_link_libraries(bench_opencv_transpose PRIVATE bench_opencv_base)

    add_executable(bench_opencv_convert src/convert.cpp)
    target_link_libraries(bench_opencv_convert PRIVATE bench_opencv_base)

    add_executable(bench_opencv_downscale src/downscale.cpp)
    target_link_libraries(bench_opencv_downscale PRIVATE bench_opencv_base)

    add_executable(bench_opencv_box_filter src/box_filter.cpp)
    target_link_libraries(bench_opencv_box_filter PRIVATE bench_opencv_base)

    add_executable(bench_opencv_lintransform src/lintransform.cpp)
    target_link_libraries(bench_opencv_lintransform PRIVATE bench_opencv_base)

    add_executable(bench_opencv_gauss_filter src/gauss_filter.cpp)
    target_link_libraries(bench_opencv_gauss_filter PRIVATE bench_opencv_base)
endif ()
