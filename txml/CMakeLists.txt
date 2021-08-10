cmake_minimum_required (VERSION 3.1)

message("WITH_XML2: ${WITH_XML2}")
message("WITH_XMLPP: ${WITH_XMLPP}")
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


#==============================================================================
set(COMPILE_DEFS "")
#find_package(LibXml2 QUIET)
#set(XML_LIBRARIES "")
set (XML_LIBS ${XML_LIBRARIES})
set (XML_INCL_DIRS ${XML_INCLUDE_DIRS})
set (XML_TARGET "")
message("LIBXML2_FOUND ${LIBXML2_FOUND}")
if(NOT LIBXML2_FOUND)
    if (WITH_XML2)
        message("SYSTEM_NAME: ${SYSTEM_NAME}")
        message("BRANCH_ROOT: ${BRANCH_ROOT}")
        if( NOT SYSTEM_NAME )
            configure_file(${BRANCH_ROOT}/cmake/download_libxml2.cmake.in libxml2-download/CMakeLists.txt)
        elseif( ${SYSTEM_NAME} STREQUAL "ANDROID" )
            configure_file(${BRANCH_ROOT}/cmake/download_android_libxml2.cmake.in libxml2-download/CMakeLists.txt)
        endif()
        # Configure & Build (optionally) `templatedXML`
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
        find_package(LibXml2 HINTS ${CMAKE_CURRENT_BINARY_DIR}/libxml2 REQUIRED)

#        foreach (lib ${LIBXML2_LIBRARIES})
#            find_library (found_lib_${lib} ${lib} HINTS ${XML_LIBRARY_DIRS} REQUIRED)
#            message("found_lib_${lib}: ${found_lib_${lib}} ")
#            list(APPEND XML_LIBS ${found_lib_${lib}})
#        endforeach()

        #set(XML_LIBS ${LIBXML2_LIBRARIES})
        #message("LIBXML2_LIBRARY: ${LIBXML2_LIBRARY}")
        #list(APPEND XML_LIBS ${LIBXML2_LIBRARY})
        #set(XML_INCL_DIRS ${LIBXML2_INCLUDE_DIRS})
        list (APPEND COMPILE_DEFS -DWITH_XML2)
        set (XML_TARGET LibXml2::LibXml2)
    else()
        message(SEND_ERROR "Failed to find LibXml2")
        return()
    endif()
else()
set (XML_TARGET LibXml2::LibXml2)
endif()


if(LIBXMLPP_INSTALLED_PATH)
    set (PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
    list(APPEND CMAKE_PREFIX_PATH ${LIBXMLPP_INSTALLED_PATH})
endif()


#-S- include(FindPkgConfig)
#-S- DO NOT Search in case of not requested!! pkg_search_module(XML REQUIRED libxml++-3.0)
#set (LIBXMLPP_INCLUDE_DIR ${LIBXML2_INCLUDE_DIR}/../libxml++-3.0/)
#include_directories(${LIBXMLPP_INCLUDE_DIR})
if(LIBXMLPP_INSTALLED_PATH)
    find_library (LIBXMLPP_LIB xml++-3.0 HINTS ${XML_LIBRARY_DIRS} REQUIRED)
    list (REMOVE_ITEM XML_LIBS xml++-3.0)
    list (APPEND XML_LIBS ${LIBXMLPP_LIB})
endif()

# Header-only library
add_library(txml INTERFACE)

#target_include_directories(
#  txml
#  INTERFACE ${XML_INCL_DIRS})

add_library(XMLImp SHARED IMPORTED)
set_property(TARGET XMLImp PROPERTY
             IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libxml2/)

add_dependencies(txml ${XML_TARGET})
message("XML_INCL_DIRS: ${XML_INCL_DIRS}")
target_include_directories(
  txml
  INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include;${CMAKE_CURRENT_SOURCE_DIR}/;${CMAKE_CURRENT_SOURCE_DIR}/applications;${XML_INCL_DIRS}>"
         "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR};include;include/applications;include/libxml2/>"
         )

target_link_libraries(
  txml
  INTERFACE ${XML_LIBS} ${XML_TARGET})

target_compile_definitions(
  txml
  INTERFACE ${COMPILE_DEFS})

#set_target_properties(txml PROPERTIES
#  PUBLIC_HEADER include/txml.hpp)

get_target_property(LIID ${XML_TARGET} INTERFACE_INCLUDE_DIRECTORIES)
message("LIID ${XML_TARGET}: ${LIID}")

#target_include_directories(
#  txml
#  INTERFACE ${LIID})

get_target_property(IID txml INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(ID txml INCLUDE_DIRECTORIES)
message("IID: ${IID}")
message("ID: ${ID}")

install(TARGETS txml
  EXPORT TemplatedXMLTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}"
  COMPONENT dev)

install(DIRECTORY include/ applications DESTINATION "${INSTALL_INCLUDE_DIR}"
        FILES_MATCHING PATTERN "*.h*")

#install(TARGETS XMLImp
#  EXPORT XMLImpTargets
#  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
#  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
#  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}"
#  COMPONENT dev)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libxml2/include/  DESTINATION "${INSTALL_INCLUDE_DIR}/.."
        FILES_MATCHING PATTERN "*.h*")
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libxml2/lib/ DESTINATION "${INSTALL_LIB_DIR}/..")
