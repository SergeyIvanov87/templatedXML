if (WITH_XML2)
    set (PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
    if (NOT LIBXML2_INSTALLED_PATH)
        find_package(LibXml2 QUIET)
    else()
        list(APPEND CMAKE_PREFIX_PATH ${LIBXML2_INSTALLED_PATH})
        message("Search LibXml2 in LIBXML2_INSTALLED_PATH: ${LIBXML2_INSTALLED_PATH}")
        find_package(LibXml2 QUIET PATHS ${LIBXML2_INSTALLED_PATH} NO_DEFAULT_PATH)
    endif()

    if (NOT TARGET LibXml2::LibXml2)
        message("Download LibXml2 from repositories")
        if( NOT SYSTEM_NAME )
            configure_file(${BRANCH_ROOT}/cmake/download_libxml2.cmake.in libxml2-download/CMakeLists.txt)
        elseif( ${SYSTEM_NAME} STREQUAL "ANDROID" )
            configure_file(${BRANCH_ROOT}/cmake/download_android_libxml2.cmake.in libxml2-download/CMakeLists.txt)
        endif()
        execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                        RESULT_VARIABLE result
                        OUTPUT_VARIABLE output
                        ERROR_VARIABLE output
                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libxml2-download )
        if(result)
            message(FATAL_ERROR "CMake step for LibXml2 failed: ${result}. Log: ${output}")
        endif()

        execute_process(COMMAND ${CMAKE_COMMAND} --build . --parallel 4
                        RESULT_VARIABLE result
                        OUTPUT_VARIABLE output
                        ERROR_VARIABLE output
                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libxml2-download )
        if(result)
            message(FATAL_ERROR "Build step for LibXml2 failed: ${result}. Log: ${output}")
        endif()
        message("LibXml2 Build Log: ${output}")

        find_package(LibXml2 REQUIRED PATHS ${LIBXML2_INSTALLED_PATH}  NO_DEFAULT_PATH)

        list (APPEND COMPILE_DEFS -DWITH_XML2)
        set (XML_TARGET LibXml2::LibXml2)
    else()
        set (XML_TARGET LibXml2::LibXml2)
        list (APPEND COMPILE_DEFS -DWITH_XML2)
    endif()
endif()
