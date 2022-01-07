include(ExternalProject)

# --------------------------------------------------------------------

# Google Test

# --------------------------------------------------------------------

message(STATUS "ExternalProject: googletest")

ExternalProject_Add(
        googletest
        UPDATE_DISCONNECTED ON
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG "release-1.11.0"
        INSTALL_COMMAND ""
)

# --------------------------------------------------------------------

# Google Benchmark

# --------------------------------------------------------------------

message(STATUS "ExternalProject: google/benchmark")

ExternalProject_Get_property(googletest SOURCE_DIR)

ExternalProject_Add(
        google_benchmark
        UPDATE_DISCONNECTED ON
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG "v1.6.0"
        INSTALL_COMMAND ""
        CMAKE_CACHE_ARGS -DGOOGLETEST_PATH:PATH=${SOURCE_DIR}
)

unset(SOURCE_DIR)

add_dependencies(google_benchmark googletest)

# --------------------------------------------------------------------
