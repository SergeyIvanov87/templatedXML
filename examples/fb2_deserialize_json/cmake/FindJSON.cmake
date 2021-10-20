set (PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
set (JSON_PACKAGE_NAME nlohmann_json)
set (JSON_TARGET nlohmann_json::nlohmann_json)

if (NOT JSON_INSTALLED_PATH)
    find_package(${JSON_PACKAGE_NAME} QUIET)
else()
    list(APPEND CMAKE_PREFIX_PATH ${JSON_INSTALLED_PATH})
    message("Search ${JSON_PACKAGE_NAME} in JSON_INSTALLED_PATH: ${JSON_INSTALLED_PATH}")
    find_package(${JSON_PACKAGE_NAME} QUIET PATHS ${JSON_INSTALLED_PATH} NO_DEFAULT_PATH)
    endif()

if (NOT TARGET ${JSON_TARGET})
    message("Download ${JSON_PACKAGE_NAME} from repositories")
    configure_file(${BRANCH_ROOT}/cmake/download_json.cmake.in json-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                    RESULT_VARIABLE result
                    OUTPUT_VARIABLE output
                    ERROR_VARIABLE output
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/json-download )
    if(result)
        message(FATAL_ERROR "CMake step for ${JSON_PACKAGE_NAME} failed: ${result}. Log: ${output}")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} --build . --parallel 4
                    RESULT_VARIABLE result
                    OUTPUT_VARIABLE output
                    ERROR_VARIABLE output
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/json-download )
    if(result)
        message(FATAL_ERROR "Build step for ${JSON_PACKAGE_NAME} failed: ${result}. Log: ${output}")
    endif()
    message("${JSON_PACKAGE_NAME} Build Log: ${output}")

    find_package(${JSON_PACKAGE_NAME} REQUIRED PATHS ${JSON_INSTALLED_PATH}  NO_DEFAULT_PATH)

    list (APPEND COMPILE_DEFS -DWITH_JSON)
    set (JSON_TARGET ${JSON_TARGET})
else()
    set (JSON_TARGET ${JSON_TARGET})
    list (APPEND COMPILE_DEFS -DWITH_JSON)
endif()
