add_subdirectory(fb2)
add_subdirectory(xdxf)
add_subdirectory(xdxf_to_fb2)

add_custom_target(examples
                DEPENDS templatedxml_fb2 templatedxml_xdxf templatedxml_xdxf_to_fb2)

install(TARGETS templatedxml_fb2 templatedxml_xdxf templatedxml_xdxf_to_fb2
  EXPORT TemplatedXMLTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
