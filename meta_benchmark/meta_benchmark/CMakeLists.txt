project(meta_base)

add_library(meta_benchmark INTERFACE)

target_include_directories(meta_benchmark INTERFACE include)
target_link_libraries(meta_benchmark INTERFACE benchmark)

add_subdirectory(test)
