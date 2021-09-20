#ifndef FB2_DOCUMENT_INFO_HPP
#define FB2_DOCUMENT_INFO_HPP
#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/fb2/DocumentInfo.h>
#include <txml/applications/fb2/Empty.hpp>

const char *DocumentInfo::name() const noexcept
{
    return DocumentInfo::class_name();
}

template<class Tracer>
void DocumentInfo::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << DocumentInfo::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << DocumentInfo::class_name() << ">\n";
}
#endif
