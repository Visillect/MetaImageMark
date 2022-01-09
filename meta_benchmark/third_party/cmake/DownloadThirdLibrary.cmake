include(ProcessorCount)

set(THIRD_PARTY_INSTALL_DIR ${CMAKE_BINARY_DIR}/third_party)

ProcessorCount(ProcCnt)

function(build_third_library PACKAGE_NAME PACKAGE_DIR)
    message(STATUS "Configuring package ${PACKAGE_NAME}")
    execute_process(COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR}
            -S ${PACKAGE_DIR} -B ${PACKAGE_DIR}/build
            -DCMAKE_INSTALL_PREFIX:PATH=${THIRD_PARTY_INSTALL_DIR}
            ${ARGN}
            RESULT_VARIABLE result OUTPUT_QUIET)
    if (result)
        message(FATAL_ERROR "Package ${PACKAGE_NAME} configure step failed: ${result}")
    endif ()

    message(STATUS "Building package ${PACKAGE_NAME}")
    execute_process(COMMAND ${CMAKE_COMMAND} --build ${PACKAGE_DIR}/build
            --parallel ${ProcCnt}
            RESULT_VARIABLE result OUTPUT_QUIET)
    if (result)
        message(FATAL_ERROR "Package ${PACKAGE_NAME} build step failed: ${result}")
    endif ()

    message(STATUS "Installing package ${PACKAGE_NAME}")
    execute_process(COMMAND ${CMAKE_COMMAND} --install ${PACKAGE_DIR}/build
            RESULT_VARIABLE result OUTPUT_QUIET)
    if (result)
        message(FATAL_ERROR "Package ${PACKAGE_NAME} install step failed: ${result}")
    endif ()
endfunction()

function(find_or_build_library PACKAGE_NAME PACKAGE_DIR)
    message(STATUS "Trying to find package ${PACKAGE_NAME}")
    find_package(${PACKAGE_NAME} QUIET)
    if (${PACKAGE_NAME}_FOUND)
        message(STATUS "Found package ${PACKAGE_NAME}")
        return()
    endif ()

    # Ignore by now
    #    if (NOT ALLOW_DOWNLOAD)
    #        message(FATAL_ERROR "Couldn't find package ${PACKAGE_NAME} and download is not allowed")
    #    endif ()

    message(STATUS "Package ${PACKAGE_NAME} was not found. Trying to download and build")
    build_third_library(${PACKAGE_NAME} ${PACKAGE_DIR} "${ARGN}")
    set(${PACKAGE_NAME}_ROOT ${THIRD_PARTY_INSTALL_DIR})
    find_package(${PACKAGE_NAME} QUIET)
    if (NOT ${PACKAGE_NAME}_FOUND)
        message(FATAL_ERROR "Couldn't find installed package ${PACKAGE_NAME}")
    endif ()
    message(STATUS "Successfully installed package ${PACKAGE_NAME}")
endfunction()
