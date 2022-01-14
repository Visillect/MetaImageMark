project(minimg_benchmark)

# Add no-as-needed flag to prevent libminbase.so elimination in executable
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-as-needed")

function(ADD_MINIMG_LIBRARY NAME TARGET)
    set(${NAME}_INCLUDE_DIR "" CACHE PATH "Path to MinImg ${TARGET} include \
        directory")
    set(${NAME}_LIBRARY "" CACHE PATH "Path to MinImg ${TARGET} dynamic library")

    if (NOT (EXISTS ${${NAME}_INCLUDE_DIR}) OR NOT (EXISTS ${${NAME}_LIBRARY}))
        message(FATAL_ERROR "Can't find ${TARGET}. Set valid ${NAME}_INCLUDE_DIR \
                and ${NAME}_LIBRARY")
    endif ()

    add_library(${TARGET} SHARED IMPORTED)
    set_target_properties(${TARGET} PROPERTIES IMPORTED_LOCATION ${${NAME}_LIBRARY})
    set_target_properties(${TARGET} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
            ${${NAME}_INCLUDE_DIR})
endfunction()

ADD_MINIMG_LIBRARY(MINBASE minbase)
ADD_MINIMG_LIBRARY(MINIMGAPI minimgapi)
ADD_MINIMG_LIBRARY(MINIMGPRC minimgprc)

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
