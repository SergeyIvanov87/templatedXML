list (APPEND EXAMPLE_TARGETS templatedxml_xdxf
                             templatedxml_xdxf_to_fb2
                             templatedxml_xdxf_to_schema
                             templatedxml_fb2
                             templatedxml_fb2_to_schema
                             templatedxml_fb2_deserialize)


add_subdirectory(fb2)
add_subdirectory(xdxf)
add_subdirectory(xdxf_to_fb2)
add_subdirectory(xdxf_to_schema)
add_subdirectory(fb2_to_schema)
add_subdirectory(fb2_deserialize)
if (WITH_JSON_EXAMPLE)
    add_subdirectory(fb2_deserialize_json)
    list (APPEND EXAMPLE_TARGETS templatedxml_fb2_deserialize_json)
endif()

set (EXAMPLE_TARGETS_EXPORT ${EXAMPLE_TARGETS} PARENT_SCOPE)
add_custom_target(examples DEPENDS ${EXAMPLE_TARGETS})

install(TARGETS ${EXAMPLE_TARGETS}
        EXPORT TXmlTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
