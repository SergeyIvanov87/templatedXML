if (WITH_XML2)
    set (PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
    if (NOT LIBXML2_INSTALLED_PATH)
        find_package(LibXml2 QUIET)
    else()
        list(APPEND CMAKE_PREFIX_PATH ${LIBXML2_INSTALLED_PATH})
        message("LIBXML2_INSTALLED_PATH: ${LIBXML2_INSTALLED_PATH}")
        find_package(LibXml2 QUIET PATHS ${LIBXML2_INSTALLED_PATH} NO_DEFAULT_PATH)
    endif()
    #if(NOT LIBXML2_FOUND)
    if (NOT TARGET LibXml2::LibXml2)
        message("Try to download and configure Xml2")
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
            message(FATAL_ERROR "CMake step for libxml2 failed: ${result}. Log: ${output}")
        endif()

        execute_process(COMMAND ${CMAKE_COMMAND} --build . --parallel 4
                        RESULT_VARIABLE result
                        OUTPUT_VARIABLE output
                        ERROR_VARIABLE output
                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libxml2-download )
        if(result)
            message(FATAL_ERROR "Build step for libxml2 failed: ${result}. Log: ${output}")
        endif()
        message("Xml build Log: ${output}")

        set (PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
        list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/libxml2)
        #find_package(LibXml2  REQUIRED)
        find_package(LibXml2 REQUIRED PATHS ${CMAKE_CURRENT_BINARY_DIR}/libxml2  NO_DEFAULT_PATH)
        list (APPEND COMPILE_DEFS -DWITH_XML2)
        set (XML_TARGET LibXml2::LibXml2)
        set (LIBXML2_INSTALLED_PATH ${CMAKE_CURRENT_BINARY_DIR}/libxml2)
    else()
        set (XML_TARGET LibXml2::LibXml2)
    endif()
endif()

add_subdirectory(fb2)
add_subdirectory(xdxf)
add_subdirectory(xdxf_to_fb2)

add_custom_target(examples
                DEPENDS templatedxml_fb2 templatedxml_xdxf templatedxml_xdxf_to_fb2)

install(TARGETS templatedxml_fb2 templatedxml_xdxf templatedxml_xdxf_to_fb2
  EXPORT TemplatedXMLTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
