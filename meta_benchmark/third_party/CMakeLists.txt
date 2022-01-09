list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(DownloadThirdLibrary)

include(FetchContent)

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
