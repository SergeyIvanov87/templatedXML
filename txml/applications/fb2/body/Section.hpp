#ifndef FB2_SECTION_HPP
#define FB2_SECTION_HPP
#include <iostream>

#include <txml/XMLSerializable.hpp>
#include <txml/XMLCreator.hpp>
#include <txml/XMLNode.hpp>
#include <txml/XMLArrayContainerNode.hpp>
#include <txml/applications/fb2/body/Section.h>
#include <txml/applications/fb2/common/Paragraph.hpp>

const char *Section::name() const noexcept
{
    return Section::class_name();
}

template<class Tracer>
void Section::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Section::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << Section::class_name() << ">\n";
}
#endif
