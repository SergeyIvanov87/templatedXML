#ifndef FB2_DESCRIPTION_HPP
#define FB2_DESCRIPTION_HPP
#include <iostream>

#include <txml/XMLSerializable.hpp>
#include <txml/XMLCreator.hpp>
#include <txml/XMLNode.hpp>

#include <txml/applications/fb2/Description.h>
#include <txml/applications/fb2/TitleInfo.hpp>
#include <txml/applications/fb2/DocumentInfo.hpp>
#include <txml/applications/fb2/PublishInfo.hpp>

const char *Description::name() const noexcept
{
    return Description::class_name();
}

template<class Tracer>
void Description::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Description::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << Description::class_name() << ">\n";
}
#endif
