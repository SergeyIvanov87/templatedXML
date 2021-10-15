#ifndef FB2_SECTION_HPP
#define FB2_SECTION_HPP
//??? #include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>
#include <txml/include/XMLArrayContainerNode.hpp>

#include <txml/applications/fb2/body/include/fwd/Section.h>

#include <txml/applications/fb2/common/include/Paragraph.hpp>

namespace fb2
{
const char *Section::name() const noexcept
{
    return Section::class_name();
}
} // namespace fb2
#endif
