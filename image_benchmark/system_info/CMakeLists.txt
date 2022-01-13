project(system_info)

add_library(system_info STATIC src/system_info.cpp)
target_include_directories(system_info PUBLIC include)

add_executable(test_string_proc src/test_string_proc.cpp)
target_link_libraries(test_string_proc gtest_main)
gtest_discover_tests(test_string_proc)
