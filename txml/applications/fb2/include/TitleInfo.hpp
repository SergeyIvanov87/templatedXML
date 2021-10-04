#ifndef FB2_TITLE_INFO_HPP
#define FB2_TITLE_INFO_HPP
#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/fb2/include/fwd/TitleInfo.h>
#include <txml/applications/fb2/include/BookTitle.hpp>

namespace fb2
{
const char *TitleInfo::name() const noexcept
{
    return TitleInfo::class_name();
}

template<class Tracer>
void TitleInfo::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << TitleInfo::class_name() << ">";
    this->serialize_elements(out, tracer, txml::no_sep);
    out << "</" << TitleInfo::class_name() << ">\n";
}

template<class Formatter, class Tracer>
void TitleInfo::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.template map<TitleInfo>(tracer);
}
} // namespace fb2
#endif
