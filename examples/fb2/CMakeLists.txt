cmake_minimum_required (VERSION 3.1)

set (PROC_NAME "templatedxml_fb2")
project(${PROC_NAME})

set (BRANCH_ROOT ${CMAKE_SOURCE_DIR})
get_filename_component(BRANCH_ROOT ${BRANCH_ROOT} ABSOLUTE)

set (PROCESS_DIR ${CMAKE_SOURCE_DIR})
get_filename_component(PROCESS_DIR ${PROCESS_DIR} ABSOLUTE)

set (BRANCH_NAME ${PROC_NAME})

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

set (3PP_INC_PATH ${LIBXML_CPP_INCLUDE_DIR}
                  ${LIBXMLPP_INCLUDE_DIR})

#Headers dir
set (INC_DIRECTORIES ${DIRECTORIES}
                     ${3PP_INC_PATH})

#Source dir
set (SRC_DIRECTORIES ${DIRECTORIES})

#==============================================================================
#Compile flags
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -O0 -g3 -fvar-tracking -MD -Wall -Wno-invalid-offsetof ")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fPIC -O0 -g3 -fvar-tracking -MD -Wall -Wno-invalid-offsetof ")

#DEBUG option
list (APPEND DEFINES_ALL -DDEBUG)

#==============================================================================
# Libraries
find_library (LIB_M m)
list (APPEND LIBS ${LIB_M})
#==============================================================================
list(REMOVE_DUPLICATES INC_DIRECTORIES)
list(REMOVE_DUPLICATES SRC_DIRECTORIES)
list(REMOVE_DUPLICATES DEFINES_ALL)


add_definitions(${DEFINES_ALL})

foreach (_dir ${SRC_DIRECTORIES})
    file(GLOB _src ${_dir}/*.cpp)
    list(APPEND SRC_ALL ${_src})

    file(GLOB _src ${_dir}/*.c)
    list(APPEND SRC_ALL ${_src})
endforeach()

include_directories(${INC_DIRECTORIES})
include_directories(${3PP_INCLUDES_DIR})
include_directories(${CMAKE_SOURCE_DIR})

foreach (_lib ${LIBS})
    message(${_lib})
endforeach()


#==============================================================================
# Setup project

add_executable(${PROC_NAME} ${SRC_ALL})
target_link_libraries(${PROC_NAME} ${LIBS} txml)

install(TARGETS ${PROC_NAME}
  EXPORT examples
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
