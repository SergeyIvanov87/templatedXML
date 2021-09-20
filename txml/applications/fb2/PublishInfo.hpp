#ifndef FB2_PUBLISH_INFO_HPP
#define FB2_PUBLISH_INFO_HPP
#include <iostream>

#include <txml/XMLSerializable.hpp>
#include <txml/XMLCreator.hpp>
#include <txml/XMLNode.hpp>

#include <txml/applications/fb2/PublishInfo.h>
#include <txml/applications/fb2/Empty.hpp>

const char *PublishInfo::name() const noexcept
{
    return PublishInfo::class_name();
}

template<class Tracer>
void PublishInfo::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << PublishInfo::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << PublishInfo::class_name() << ">\n";
}
#endif
