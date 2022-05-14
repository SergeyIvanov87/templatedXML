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
if (WITH_JSON)
    include(${BRANCH_ROOT}/cmake/FindJSON.cmake)
endif()
###############################################################

# Header-only library
add_library(TXml INTERFACE)

target_include_directories(
  TXml
  INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..;${CMAKE_CURRENT_SOURCE_DIR}/;${CMAKE_CURRENT_SOURCE_DIR}/include;${CMAKE_CURRENT_SOURCE_DIR}/applications>"
         "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR};include>"
         )
#TODO remove extra INSTALL_INTERFACE include and refactor sources
target_link_libraries(
  TXml
  INTERFACE ${XML_TARGET} ${JSON_TARGET})

target_compile_definitions(
  TXml
  INTERFACE ${COMPILE_DEFS})

add_dependencies(TXml ${XML_TARGET} ${JSON_TARGET})

#set_target_properties(TXml PROPERTIES
#  PUBLIC_HEADER include/TXml.hpp)

install(TARGETS TXml
  EXPORT TXmlTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}"
    COMPONENT dev)

install(DIRECTORY ./ ./include ./applications DESTINATION "${INSTALL_INCLUDE_DIR}"
        FILES_MATCHING PATTERN "*.h*")

install(DIRECTORY ../cmake DESTINATION "${INSTALL_LIB_DIR}"
        FILES_MATCHING PATTERN "*")
