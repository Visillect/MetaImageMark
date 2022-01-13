cmake_minimum_required(VERSION 3.15)

project(meta_image_mark)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(BuildTypes)
include(FetchContent)

enable_testing()
include(GoogleTest)

# ------------------------------------------------------------------------------
# Google Test
# ------------------------------------------------------------------------------

# Including source files to avoid linking errors.
# See https://github.com/google/googletest/blob/main/googletest/README.md
message(STATUS "Fetch google test")
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG "release-1.11.0"
)
FetchContent_MakeAvailable(googletest)


# ------------------------------------------------------------------------------
# Google benchmark
# ------------------------------------------------------------------------------

set(BENCHMARK_ENABLE_INSTALL OFF)
set(BENCHMARK_ENABLE_TESTING OFF)

# Including source files because of problems with library installation and
# to avoid potential linking problems
message(STATUS "Fetch google benchmark")
FetchContent_Declare(
        google_benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG "v1.6.0"
)
FetchContent_MakeAvailable(google_benchmark)

# ------------------------------------------------------------------------------

add_subdirectory(system_info)
add_subdirectory(grid_benchmark)

set(MINIMG_BENCHMARK ON CACHE STRING "Whether to enable the MinImg benchmark")
set(OPENCV_BENCHMARK ON CACHE STRING "Whether to enable the OpenCV benchmark")

if (${MINIMG_BENCHMARK})
    add_subdirectory(minimg_benchmark)
endif ()
if (${OPENCV_BENCHMARK})
    add_subdirectory(opencv_benchmark)
endif ()
