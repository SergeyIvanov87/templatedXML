cmake_minimum_required (VERSION 3.1)

set (PROC_NAME "templatedxml_fb2_deserialize_json")
project(${PROC_NAME})

set (BRANCH_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(BRANCH_ROOT ${BRANCH_ROOT} ABSOLUTE)

set (PROCESS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
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

include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


#==============================================================================
# Setup project
add_executable(${PROC_NAME} main.cpp)
target_link_libraries(${PROC_NAME} TXml ${XML_TARGET} nlohmann_json::nlohmann_json)
set_property(TARGET ${PROC_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)


install(TARGETS ${PROC_NAME}
  EXPORT examples
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
