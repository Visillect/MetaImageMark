# Benchmark tools

add_library(benchmark_tools INTERFACE)
target_include_directories(benchmark_tools INTERFACE include)
target_link_libraries(benchmark_tools INTERFACE minimgapi minimgprc minimgio minutils benchmark)

# Verification tools

add_library(benchmark_verification INTERFACE)
target_include_directories(benchmark_verification INTERFACE include)
target_link_libraries(benchmark_verification INTERFACE minimgapi minimgprc minimgio minutils)
