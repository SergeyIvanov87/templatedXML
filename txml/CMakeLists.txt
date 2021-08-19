cmake_minimum_required (VERSION 3.1)

if (WITH_XMLPP)
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


###############################################################
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
################################################################

# Header-only library
add_library(txml INTERFACE)

target_include_directories(
  txml
  INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include;${CMAKE_CURRENT_SOURCE_DIR}/;${CMAKE_CURRENT_SOURCE_DIR}/applications>"
         "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR};include;include/applications>"
         )

target_link_libraries(
  txml
  INTERFACE ${XML_LIBS} ${XML_TARGET})

target_compile_definitions(
  txml
  INTERFACE ${COMPILE_DEFS})

add_dependencies(txml ${XML_TARGET})

#set_target_properties(txml PROPERTIES
#  PUBLIC_HEADER include/txml.hpp)

install(TARGETS txml
  EXPORT TemplatedXMLTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}"
    COMPONENT dev)

install(DIRECTORY include/ applications DESTINATION "${INSTALL_INCLUDE_DIR}"
        FILES_MATCHING PATTERN "*.h*")

install(DIRECTORY ../cmake DESTINATION "${INSTALL_LIB_DIR}"
        FILES_MATCHING PATTERN "*")
