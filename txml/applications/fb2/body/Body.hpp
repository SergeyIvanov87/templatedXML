#ifndef FB2_BODY_HPP
#define FB2_BODY_HPP
#include <iostream>

#include <txml/XMLSerializable.hpp>
#include <txml/XMLCreator.hpp>
#include <txml/XMLNode.hpp>
#include <txml/XMLArrayContainerNode.hpp>
#include <txml/applications/fb2/body/Body.h>
#include <txml/applications/fb2/body/Section.hpp>

const char *Body::name() const noexcept
{
    return Body::class_name();
}

template<class Tracer>
void Body::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Body::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << Body::class_name() << ">\n";
}
#endif
