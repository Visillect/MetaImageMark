include(FetchContent)

function(bench_add_library LIBRARY)
    if (NOT ${DOWNLOAD_DEPENDENCIES})
        find_package(${LIBRARY} REQUIRED)
        return()
    endif ()

    message(STATUS "Trying to find library ${LIBRARY}")
    find_package(${LIBRARY} QUIET)
    if (${LIBRARY}_Found)
        message(STATUS "Found ${LIBRARY}")
    else ()
        message(STATUS "${LIBRARY} was not found. Fetching.")
        FetchContent_Declare(
                ${LIBRARY}_fetch
                GIT_REPOSITORY https://github.com/google/googletest.git
                GIT_TAG "release-1.11.0"
        )
        FetchContent_MakeAvailable(${LIBRARY}_fetch)
    endif ()
endfunction()

# ------------------------------------------------------------------------------
# Google Test
# ------------------------------------------------------------------------------
if (${ENABLE_TESTS})
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    bench_add_library(GTest)
endif ()

# ------------------------------------------------------------------------------
# Google benchmark
# ------------------------------------------------------------------------------


set(BENCHMARK_ENABLE_INSTALL OFF)
set(BENCHMARK_ENABLE_TESTING OFF)

bench_add_library(benchmark)

# ------------------------------------------------------------------------------
