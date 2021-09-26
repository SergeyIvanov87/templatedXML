#ifndef FB2_DOCUMENT_INFO_HPP
#define FB2_DOCUMENT_INFO_HPP
#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/fb2/include/fwd/DocumentInfo.h>
#include <txml/applications/fb2/include/Empty.hpp>

namespace fb2
{
const char *DocumentInfo::name() const noexcept
{
    return DocumentInfo::class_name();
}

template<class Tracer>
void DocumentInfo::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << DocumentInfo::class_name() << ">";
    this->serialize_elements(out, tracer, txml::no_sep);
    out << "</" << DocumentInfo::class_name() << ">\n";
}

template<class Formatter, class Tracer>
void DocumentInfo::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.template map<DocumentInfo>(tracer);
}
} // namespace fb2
#endif
