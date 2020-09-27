cmake_minimum_required (VERSION 2.8)

project(TemplatedXML CXX)

set(TEMPLATEDXML_MAJOR_VERSION 0)
set(TEMPLATEDXML_MINOR_VERSION 1)
set(TEMPLATEDXML_PATCH_VERSION 0)
set(TEMPLATEDXML_VERSION
    ${TEMPLATEDXML_MAJOR_VERSION}.${TEMPLATEDXML_MINOR_VERSION}.${TEMPLATEDXML_PATCH_VERSION})


set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")

if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/TemplatedXML)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")


foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()


include_directories(
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_BINARY_DIR}")


add_subdirectory(txml)
add_subdirectory(examples)

# Add all targets to the build-tree export set
export(TARGETS txml templatedxml_fb2 templatedxml_xdxf
    FILE "${PROJECT_BINARY_DIR}/TemplatedXMLTargets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE TemplatedXML)

 #Create the TemplatedXMLConfig.cmake and TemplatedXMLConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(TemplatedXMLConfig.cmake.in
  "${PROJECT_BINARY_DIR}/TemplatedXMLConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${PROJECT_SOURCE_DIR}/${REL_INCLUDE_DIR}")
configure_file(TemplatedXMLConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/TemplatedXMLConfig.cmake" @ONLY)
# ... for both
configure_file(TemplatedXMLConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/TemplatedXMLConfigVersion.cmake" @ONLY)

# Install the FooBarConfig.cmake and TemplatedXMLConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/TemplatedXMLConfig.cmake"
  "${PROJECT_BINARY_DIR}/TemplatedXMLConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT TemplatedXMLTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)
