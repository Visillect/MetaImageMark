project(meta_base)

add_library(meta_base INTERFACE)

target_include_directories(meta_base INTERFACE include)
target_link_libraries(meta_base INTERFACE benchmark)

add_subdirectory(test)
