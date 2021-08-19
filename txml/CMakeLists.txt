cmake_minimum_required (VERSION 3.1)

###############################################################
if (WITH_XMLPP)
    include(${BRANCH_ROOT}/cmake/FindLibXMLPP.cmake)
endif()
###############################################################
if (WITH_XML2)
    include(${BRANCH_ROOT}/cmake/FindLibXML2.cmake)
endif()
###############################################################

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
  INTERFACE ${XML_TARGET})

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
