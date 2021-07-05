cmake_minimum_required (VERSION 3.1)

set (BRANCH_ROOT ${CMAKE_SOURCE_DIR})
get_filename_component(BRANCH_ROOT ${BRANCH_ROOT} ABSOLUTE)

set (PROCESS_DIR ${CMAKE_SOURCE_DIR})
get_filename_component(PROCESS_DIR ${PROCESS_DIR} ABSOLUTE)

#==============================================================================
if(LIBXMLPP_INSTALLED_PATH)
	set (PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
	list(APPEND CMAKE_PREFIX_PATH ${LIBXMLPP_INSTALLED_PATH})
endif()

find_package(LibXml2 REQUIRED)
if(NOT LIBXML2_FOUND)
    message(SEND_ERROR "Failed to find LibXml2")
    return()
endif()

include(FindPkgConfig)
pkg_search_module(XML REQUIRED libxml++-3.0)
#set (LIBXMLPP_INCLUDE_DIR ${LIBXML2_INCLUDE_DIR}/../libxml++-3.0/)
#include_directories(${LIBXMLPP_INCLUDE_DIR})
if(LIBXMLPP_INSTALLED_PATH)
	find_library (LIBXMLPP_LIB xml++-3.0 HINTS ${XML_LIBRARY_DIRS} REQUIRED)
	list (REMOVE_ITEM XML_LIBRARIES xml++-3.0)
	list (APPEND XML_LIBRARIES ${LIBXMLPP_LIB})
endif()

# Header-only library
add_library(txml INTERFACE)

target_include_directories(
  txml
  INTERFACE ${XML_INCLUDE_DIRS})

target_include_directories(
  txml
  INTERFACE
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include;${CMAKE_CURRENT_SOURCE_DIR}/;${CMAKE_CURRENT_SOURCE_DIR}/applications>"
         "$<INSTALL_INTERFACE:include;include/applications>"
         )
            
target_link_libraries(
  txml
  INTERFACE ${XML_LIBRARIES})


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
