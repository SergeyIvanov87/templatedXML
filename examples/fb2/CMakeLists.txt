cmake_minimum_required (VERSION 3.1)

set (PROC_NAME "templatedxml_fb2")
project(${PROC_NAME})

set (BRANCH_ROOT ${CMAKE_SOURCE_DIR})
get_filename_component(BRANCH_ROOT ${BRANCH_ROOT} ABSOLUTE)

set (PROCESS_DIR ${CMAKE_SOURCE_DIR})
get_filename_component(PROCESS_DIR ${PROCESS_DIR} ABSOLUTE)

set (BRANCH_NAME ${PROC_NAME})

#==============================================================================
#Compile flags
set (CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

#==============================================================================
# Setup project
add_executable(${PROC_NAME} main.cpp)
target_link_libraries(${PROC_NAME} txml ${XML_TARGET})
set_property(TARGET ${PROC_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)


install(TARGETS ${PROC_NAME}
  EXPORT examples
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
