project(meta_base)

add_library(grid_benchmark INTERFACE)

target_include_directories(grid_benchmark INTERFACE include)
target_link_libraries(grid_benchmark INTERFACE benchmark)

add_subdirectory(test)
