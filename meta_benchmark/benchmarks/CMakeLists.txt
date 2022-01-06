# binary_operations

find_package(OpenCV)

add_subdirectory(src)

add_library(benchmarks INTERFACE)
target_include_directories(benchmarks INTERFACE include)
