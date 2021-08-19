###############################################################
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

#include(ExternalProject)
 #       ExternalProject_Get_Property(libxml2 INSTALL_DIR)
  #      message("Source dir of libxml2 = ${INSTALL_DIR}")

        set (PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
        list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/libxml2)
        #find_package(LibXml2  REQUIRED)
        find_package(LibXml2 REQUIRED PATHS ${LIBXML2_INSTALLED_PATH}  NO_DEFAULT_PATH)
        list (APPEND COMPILE_DEFS -DWITH_XML2)

        set (XML_TARGET LibXml2::LibXml2)
        #set (LIBXML2_INSTALLED_PATH ${CMAKE_CURRENT_BINARY_DIR}/libxml2)
    else()
        set (XML_TARGET LibXml2::LibXml2)
        list (APPEND COMPILE_DEFS -DWITH_XML2)
    endif()
endif()
