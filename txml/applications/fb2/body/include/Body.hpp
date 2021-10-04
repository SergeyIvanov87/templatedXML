#ifndef FB2_BODY_HPP
#define FB2_BODY_HPP
#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>
#include <txml/include/XMLArrayContainerNode.hpp>

#include <txml/applications/fb2/body/fb2_body_fwd.h>


namespace fb2
{
const char *Body::name() const noexcept
{
    return Body::class_name();
}

template<class Tracer>
void Body::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Body::class_name() << ">";
    this->serialize_elements(out, tracer, txml::no_sep);
    out << "</" << Body::class_name() << ">\n";
}

template<class Formatter, class Tracer>
void Body::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.template map<Body>(tracer);
}
} // namespace fb2
#endif
