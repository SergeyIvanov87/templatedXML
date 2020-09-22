cmake_minimum_required (VERSION 2.8)


set (BRANCH_ROOT ${CMAKE_SOURCE_DIR})
get_filename_component(BRANCH_ROOT ${BRANCH_ROOT} ABSOLUTE)

set (PROCESS_DIR ${CMAKE_SOURCE_DIR})
get_filename_component(PROCESS_DIR ${PROCESS_DIR} ABSOLUTE)

#==============================================================================

#Common Directories
set (DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

#3PP Directories
find_package(LibXml2 REQUIRED)
if(NOT LIBXML2_FOUND)
    message(SEND_ERROR "Failed to find LibXml2")
    return()
else()
    include(FindPkgConfig)
    pkg_search_module(XML REQUIRED libxml++-3.0)
    message("PKG_Config: ${XML_INCLUDE_DIRS}")

    set (LIBXMLPP_INCLUDE_DIR ${LIBXML2_INCLUDE_DIR}/../libxml++-3.0/)
    list (APPEND LIBXMLPP_INCLUDE_DIR ${XML_INCLUDE_DIRS})
    include_directories(${LIBXMLPP_INCLUDE_DIR})
    find_library (LIBXMLPP_LIB xml++-3.0)
    if(LIBXMLPP_LIB STREQUAL "LIBXMLPP_LIB_-NOTFOUND")
        message(SEND_ERROR "Failed to find libxml++-3.0 library.")
        message(${LIBXMLPP_LIB})
        return()
    endif()
    list (APPEND LIBS ${LIBXMLPP_LIB} ${XML_LIBRARIES})
endif()

set (LIB_XML_INCLUDE_PATH ${LIBXML_CPP_INCLUDE_DIR}
                          ${LIBXMLPP_INCLUDE_DIR})

#Headers dir
set (INC_DIRECTORIES    ${LIB_XML_INCLUDE_PATH}
                        ${DIRECTORIES}
                        ${DIRECTORIES}/applications
                        ${DIRECTORIES}/include)

list(REMOVE_DUPLICATES INC_DIRECTORIES)

set(SELF_INCLUDE_DIRS applications
                      include)
file(GLOB public_headers ${SELF_INCLUDE_DIRS}/*.hpp)

message("public_headers: ${public_headers}")
add_library(txml INTERFACE)
#include_directories(${INC_DIRECTORIES})

message("CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(
  txml
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/{include,./,applications}>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>)
link_libraries(${LIBS})

set_target_properties(txml PROPERTIES
  PUBLIC_HEADER "include/XDXFCreatable.h")

install(TARGETS txml
  # IMPORTANT: Add the txml library to the "export-set"
  EXPORT TemplatedXMLTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/txml"
    COMPONENT dev)
