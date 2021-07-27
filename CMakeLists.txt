cmake_minimum_required (VERSION 3.1)

project(TemplatedXML CXX)

# configure version
set(TEMPLATEDXML_MAJOR_VERSION 0)
set(TEMPLATEDXML_MINOR_VERSION 1)
set(TEMPLATEDXML_PATCH_VERSION 0)
set(TEMPLATEDXML_VERSION
    ${TEMPLATEDXML_MAJOR_VERSION}.${TEMPLATEDXML_MINOR_VERSION}.${TEMPLATEDXML_PATCH_VERSION})

set(WITH_XMLPP OFF CACHE BOOL "Configure with libxml++")
set(WITH_XML2 OFF CACHE BOOL "Configure with libxml2")

# set install_path's
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")

if(WIN32 AND NOT CYGWIN)
  set(DEFAULT_INSTALL_CMAKE_DIR CMake)
else()
  set(DEFAULT_INSTALL_CMAKE_DIR lib/CMake/TemplatedXML)
endif()

set(INSTALL_CMAKE_DIR ${DEFAULT_INSTALL_CMAKE_DIR} CACHE PATH   "Installation directory for CMake files")

# make install_path's absolute
foreach(var LIB BIN INCLUDE CMAKE)
  set(path INSTALL_${var}_DIR)
  if(NOT IS_ABSOLUTE "${${path}}")
    set(${path} "${CMAKE_INSTALL_PREFIX}/${${path}}")
  endif()
endforeach()


include_directories(
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_BINARY_DIR}")


add_subdirectory(txml)
add_subdirectory(examples)

export(TARGETS txml templatedxml_fb2 templatedxml_xdxf templatedxml_xdxf_to_fb2
    FILE "${PROJECT_BINARY_DIR}/TemplatedXMLTargets.cmake")

export(PACKAGE TemplatedXML)

file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")

set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(TemplatedXMLConfig.cmake.in
  "${PROJECT_BINARY_DIR}/TemplatedXMLConfig.cmake" @ONLY)

set(CONF_INCLUDE_DIRS "\${PROJECT_SOURCE_DIR}/${REL_INCLUDE_DIR}")
configure_file(TemplatedXMLConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/TemplatedXMLConfig.cmake" @ONLY)

configure_file(TemplatedXMLConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/TemplatedXMLConfigVersion.cmake" @ONLY)

install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/TemplatedXMLConfig.cmake"
  "${PROJECT_BINARY_DIR}/TemplatedXMLConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

install(EXPORT TemplatedXMLTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)
