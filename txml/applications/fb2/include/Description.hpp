#ifndef FB2_DESCRIPTION_HPP
#define FB2_DESCRIPTION_HPP
#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/fb2/include/fwd/Description.h>
#include <txml/applications/fb2/include/TitleInfo.hpp>
#include <txml/applications/fb2/include/DocumentInfo.hpp>
#include <txml/applications/fb2/include/PublishInfo.hpp>

namespace fb2
{
const char *Description::name() const noexcept
{
    return Description::class_name();
}

template<class Tracer>
void Description::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Description::class_name() << ">";
    this->serialize_elements(out, tracer, txml::no_sep);
    out << "</" << Description::class_name() << ">\n";
}

template<class Formatter, class Tracer>
void Description::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.template map<Description>(tracer);
}
} // namespace fb2
#endif
