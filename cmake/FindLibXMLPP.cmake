
if (WITH_XMLPP)
    message (FATAL_ERROR "Not supported by now")
    configure_file(${BRANCH_ROOT}/cmake/download_libxml++.cmake.in libxml++-download/CMakeLists.txt)
    # Configure & Build (optionally) `templatedXML`
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                    RESULT_VARIABLE result
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libxml++-download )
    if(result)
        message(FATAL_ERROR "CMake step for libxml++ failed: ${result}")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
                    RESULT_VARIABLE result
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libxml++-download )
    if(result)
        message(FATAL_ERROR "Build step for libxml++ failed: ${result}")
    endif()
endif()

if(LIBXMLPP_INSTALLED_PATH)
    find_library (LIBXMLPP_LIB xml++-3.0 HINTS ${XML_LIBRARY_DIRS} REQUIRED)
    list (REMOVE_ITEM XML_LIBS xml++-3.0)
    list (APPEND XML_LIBS ${LIBXMLPP_LIB})
endif()


XML_TARGET = XML_LIBS
