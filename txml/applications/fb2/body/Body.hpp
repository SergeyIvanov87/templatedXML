#ifndef FB2_BODY_HPP
#define FB2_BODY_HPP
#include <iostream>

#include "fb2/body/Body.h"
#include "fb2/body/Section.hpp"

#include "XMLSerializable.hpp"
#include "XMLCreator.hpp"
#include "XMLNode.hpp"
#include "XMLArrayContainerNode.hpp"

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
