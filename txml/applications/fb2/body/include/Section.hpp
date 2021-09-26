#ifndef FB2_SECTION_HPP
#define FB2_SECTION_HPP
//??? #include <iostream>

#include <txml/include/XMLSerializable.hpp>
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

template<class Tracer>
void Section::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Section::class_name() << ">";
    this->serialize_elements(out, tracer, txml::no_sep);
    out << "</" << Section::class_name() << ">\n";
}

template<class Formatter, class Tracer>
void Section::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.template map<Section>(tracer);
}
} // namespace fb2
#endif
