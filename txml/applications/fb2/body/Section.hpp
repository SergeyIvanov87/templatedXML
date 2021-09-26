#ifndef FB2_SECTION_HPP
#define FB2_SECTION_HPP
#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>
#include <txml/include/XMLArrayContainerNode.hpp>
#include <txml/applications/fb2/body/Section.h>
#include <txml/applications/fb2/common/Paragraph.hpp>

namespace fb2
{
const char *Section::name() const noexcept
{
    return Section::class_name();
}

template<class Tracer>
void Section::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Section::class_name() << ">";
    this->serialize_elements(out, tracer, txml::no_sep);
    out << "</" << Section::class_name() << ">\n";
}
} // namespace fb2
#endif
