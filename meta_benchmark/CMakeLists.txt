cmake_minimum_required(VERSION 3.15)

project(meta_image_mark)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(BuildTypes)

add_subdirectory(third_party)
add_subdirectory(meta_benchmark)
