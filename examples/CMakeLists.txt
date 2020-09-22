add_subdirectory(fb2)
add_subdirectory(xdxf)


add_custom_target(examples
                DEPENDS templatedxml_fb2 templatedxml_xdxf)

install(TARGETS templatedxml_fb2 templatedxml_xdxf
  EXPORT TemplatedXMLTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
