cmake_minimum_required(VERSION 3.15)

project(meta_image_mark)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(DOWNLOAD_DEPENDENCIES OFF CACHE BOOL "Allow cmake to download dependencies")
set(ENABLE_TESTS OFF CACHE BOOL "Enable project tests")

set(ENABLE_MINIMG_BENCHMARK OFF CACHE BOOL "Whether to enable the MinImg benchmark")
set(ENABLE_OPENCV_BENCHMARK ON CACHE BOOL "Whether to enable the OpenCV benchmark")

include(Dependencies)
include(BuildTypes)

if (${ENABLE_TESTS})
    include(GoogleTest)
endif ()

add_subdirectory(system_info)
add_subdirectory(grid_benchmark)
add_subdirectory(image_benchmark)

if (${ENABLE_MINIMG_BENCHMARK})
    add_subdirectory(minimg_benchmark)
endif ()
if (${ENABLE_OPENCV_BENCHMARK})
    add_subdirectory(opencv_benchmark)
endif ()
