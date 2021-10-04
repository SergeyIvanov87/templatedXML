#ifndef FB2_PUBLISH_INFO_HPP
#define FB2_PUBLISH_INFO_HPP
#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/fb2/include/fwd/PublishInfo.h>
#include <txml/applications/fb2/include/Empty.hpp>

namespace fb2
{
const char *PublishInfo::name() const noexcept
{
    return PublishInfo::class_name();
}

template<class Tracer>
void PublishInfo::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << PublishInfo::class_name() << ">";
    this->serialize_elements(out, tracer, txml::no_sep);
    out << "</" << PublishInfo::class_name() << ">\n";
}

template<class Formatter, class Tracer>
void PublishInfo::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.template map<PublishInfo>(tracer);
}
} // namespace fb2
#endif
