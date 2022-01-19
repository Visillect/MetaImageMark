project(minimg_benchmark)

function(ADD_MINIMG_CACHE NAME)
    set(${NAME}_INCLUDE_DIR "" CACHE PATH "Path to MinImg ${TARGET} include \
        directory")
    set(${NAME}_LIBRARY "" CACHE PATH "Path to MinImg ${TARGET} dynamic library")
endfunction()

function(ADD_MINIMG_LIBRARY NAME TARGET RESULT)
    if (NOT (EXISTS ${${NAME}_INCLUDE_DIR}) AND (EXISTS ${MINIMG_INCLUDE_DIR}))
        set(${NAME}_INCLUDE_DIR ${MINIMG_INCLUDE_DIR})
    endif ()

    if (NOT (EXISTS ${${NAME}_INCLUDE_DIR}) OR NOT (EXISTS ${${NAME}_LIBRARY}))
        message(WARNING "Can't find ${TARGET}. Set valid ${NAME}_INCLUDE_DIR \
                and ${NAME}_LIBRARY. Disabling MinImg benchmarks.")
        set(${RESULT} OFF PARENT_SCOPE)
        return()
    endif ()

    add_library(${TARGET} SHARED IMPORTED)
    set_target_properties(${TARGET} PROPERTIES IMPORTED_LOCATION ${${NAME}_LIBRARY})
    set_target_properties(${TARGET} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
            ${${NAME}_INCLUDE_DIR})

    set(${RESULT} ON PARENT_SCOPE)
endfunction()

set(MINIMG_INCLUDE_DIR "" CACHE PATH "Path to MinImg include directory")
ADD_MINIMG_CACHE(MINBASE)
ADD_MINIMG_CACHE(MINIMGAPI)
ADD_MINIMG_CACHE(MINIMGPRC)

set(RESULT "")
ADD_MINIMG_LIBRARY(MINBASE minbase RESULT)
ADD_MINIMG_LIBRARY(MINIMGAPI minimgapi RESULT)
ADD_MINIMG_LIBRARY(MINIMGPRC minimgprc RESULT)

if (RESULT)
    # Add no-as-needed flag to prevent libminbase.so elimination in executable
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-as-needed")

    add_library(bench_minimg_base INTERFACE)
    target_include_directories(bench_minimg_base INTERFACE include)
    target_link_libraries(bench_minimg_base INTERFACE image_benchmark minbase
            minimgapi minimgprc)

    add_executable(bench_minimg_merge src/merge.cpp)
    target_link_libraries(bench_minimg_merge PRIVATE bench_minimg_base)

    add_executable(bench_minimg_transpose src/transpose.cpp)
    target_link_libraries(bench_minimg_transpose PRIVATE bench_minimg_base)

    add_executable(bench_minimg_convert src/convert.cpp)
    target_link_libraries(bench_minimg_convert PRIVATE bench_minimg_base)

    add_executable(bench_minimg_downscale src/downscale.cpp)
    target_link_libraries(bench_minimg_downscale PRIVATE bench_minimg_base)

    add_executable(bench_minimg_box_filter src/box_filter.cpp)
    target_link_libraries(bench_minimg_box_filter PRIVATE bench_minimg_base)

    add_executable(bench_minimg_lintransform src/lintransform.cpp)
    target_link_libraries(bench_minimg_lintransform PRIVATE bench_minimg_base)

    add_executable(bench_minimg_gauss_filter src/gauss_filter.cpp)
    target_link_libraries(bench_minimg_gauss_filter PRIVATE bench_minimg_base)
endif ()
