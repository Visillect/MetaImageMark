include(FetchContent)

# ------------------------------------------------------------------------------
# Google Test
# ------------------------------------------------------------------------------
if (${ENABLE_TESTS})
    if (NOT ${DOWNLOAD_DEPENDENCIES})
        find_package(GTest REQUIRED)
    else ()
        find_package(GTest QUIET)
        if (NOT GTest_Found)
            message(STATUS "GTest was not found. Fetching.")
            FetchContent_Declare(
                    ${LIBRARY}_fetch
                    GIT_REPOSITORY https://github.com/google/googletest.git
                    GIT_TAG "release-1.11.0"
            )
            # For Windows: Prevent overriding the parent project's
            # compiler/linker settings
            set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
            FetchContent_MakeAvailable(GTest_fetch)
        endif ()
    endif ()
endif ()

# ------------------------------------------------------------------------------
# Google benchmark
# ------------------------------------------------------------------------------

if (NOT ${DOWNLOAD_DEPENDENCIES})
    find_package(benchmark REQUIRED)
else ()
    find_package(benchmark QUIET)
    if (NOT benchmark_Found)
        message(STATUS "benchmark was not found. Fetching.")

        set(BENCHMARK_ENABLE_INSTALL OFF)
        set(BENCHMARK_ENABLE_TESTING OFF)

        FetchContent_Declare(
                benchmark_fetch
                GIT_REPOSITORY https://github.com/google/benchmark.git
                GIT_TAG "v1.6.0"
        )
        # For Windows: Prevent overriding the parent project's
        # compiler/linker settings
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(benchmark_fetch)
    endif ()
endif ()

# ------------------------------------------------------------------------------
