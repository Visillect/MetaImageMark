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

add_executable(minimg_merge_image src/merge_image.cpp src/common.h)
target_link_libraries(minimg_merge_image PRIVATE grid_benchmark minbase
        minimgapi minimgprc)
