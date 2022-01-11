include(FetchContent)

# ------------------------------------------------------------------------------
# MinImg Base
# ------------------------------------------------------------------------------

set(MINIMG_BASE_INCLUDE_DIR "" CACHE PATH "Path to MinImg minbase include \
    directory")
set(MINIMG_BASE_LIBRARY "" CACHE PATH "Path to MinImg minbase dynamic library \
    directory")

set(MINIMG_API_INCLUDE_DIR "" CACHE PATH "Path to MinImg minimgapi include \
    directory")
set(MINIMG_API_LIBRARY "" CACHE PATH "Path to MinImg minimgapi dynamic library \
    directory")

set(MINIMG_PRC_INCLUDE_DIR "" CACHE PATH "Path to MinImg minimgprc include \
    directory")
set(MINIMG_PRC_LIBRARY "" CACHE PATH "Path to MinImg minimgprc dynamic library \
    directory")

# ------------------------------------------------------------------------------
# MinImg Prc
# ------------------------------------------------------------------------------

set(MINIMG_PRC_INSTALL_DIR "" CACHE PATH "Path to minimgprc directory")

if (NOT (EXISTS ${MINIMG_PRC_INSTALL_DIR}))
    message(FATAL_ERROR "Can't find minimgprc. Set valid MINIMG_PRC_INSTALL_DIR")
endif ()

add_library(minimgprc SHARED IMPORTED)
set_target_properties(minimgprc PROPERTIES IMPORTED_LOCATION
        ${MINIMG_PRC_INSTALL_DIR})

# ------------------------------------------------------------------------------

add_executable(minimg_merge_image src/merge_image.cpp src/utils.h)
target_link_libraries(minimg_merge_image PRIVATE grid_benchmark minbase
        minimgapi minimgprc)
