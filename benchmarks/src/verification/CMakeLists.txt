if (${OpenCV_FOUND})
    add_executable(bench_verify_binary_stress stress_test/binary_operations.cpp)
    target_link_libraries(bench_verify_binary_stress PRIVATE benchmark_verification gtest "${OpenCV_LIBS}" benchmarks)

    add_executable(bench_verify_lin_transform_stress stress_test/lin_transform.cpp)
    target_link_libraries(bench_verify_lin_transform_stress PRIVATE benchmark_verification gtest "${OpenCV_LIBS}" benchmarks)

    add_executable(bench_verify_gauss_filter_stress stress_test/config.cpp)
    target_link_libraries(bench_verify_gauss_filter_stress PRIVATE benchmark_verification gtest "${OpenCV_LIBS}" benchmarks)


    add_executable(_bench_verify_aver_filter aver_filter.cpp)
    target_link_libraries(_bench_verify_aver_filter PRIVATE benchmark_verification "${OpenCV_LIBS}" benchmarks)
    add_custom_target(bench_verify_aver_filter
            $<TARGET_FILE:_bench_verify_aver_filter> ${CMAKE_CURRENT_BINARY_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/test_images/*.jpg)

    add_executable(_bench_verify_gauss_filter gauss_filter.cpp)
    target_link_libraries(_bench_verify_gauss_filter PRIVATE benchmark_verification "${OpenCV_LIBS}" benchmarks)
    add_custom_target(bench_verify_gauss_filter
            $<TARGET_FILE:_bench_verify_gauss_filter> ${CMAKE_CURRENT_BINARY_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/test_images/*.jpg)

    add_executable(_bench_verify_scale scale_image.cpp)
    target_link_libraries(_bench_verify_scale PRIVATE benchmark_verification "${OpenCV_LIBS}" benchmarks)
    add_custom_target(bench_verify_scale
            $<TARGET_FILE:_bench_verify_scale> ${CMAKE_CURRENT_BINARY_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/test_images/*.jpg)
endif ()
