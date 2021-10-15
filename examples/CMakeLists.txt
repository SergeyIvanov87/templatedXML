add_subdirectory(fb2)
add_subdirectory(xdxf)
add_subdirectory(xdxf_to_fb2)
add_subdirectory(xdxf_to_schema)
add_subdirectory(fb2_to_schema)
add_subdirectory(fb2_deserialize)

add_custom_target(examples
                DEPENDS templatedxml_fb2 templatedxml_xdxf
                        templatedxml_xdxf_to_fb2
                        templatedxml_xdxf_to_schema
                        templatedxml_fb2_to_schema
                        templatedxml_fb2_deserialize)

install(TARGETS templatedxml_fb2 templatedxml_xdxf
                templatedxml_xdxf_to_fb2
                templatedxml_xdxf_to_schema
                templatedxml_fb2_to_schema
                templatedxml_fb2_deserialize
  EXPORT TXmlTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
