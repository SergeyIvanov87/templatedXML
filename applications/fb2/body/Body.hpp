#ifndef FB2_BODY_HPP
#define FB2_BODY_HPP
#include <iostream>

#include "fb2/body/Body.h"
#include "fb2/body/Section.hpp"

#include "XMLProducible.hpp"
#include "XMLPublishing.hpp"
#include "XMLCreator.hpp"
#include "XMLNode.hpp"
#include "XMLArrayContainerNode.hpp"

const char *Body::name() const noexcept
{
    return Body::class_name();
}

template<class Tracer>
bool Body::initialize(std::string &name, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, reader, tracer);
    return true;
}

template<class Tracer>
void Body::dump(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Body::class_name() << ">";
    this->dump_all(out, tracer, no_sep);
    out << "</" << Body::class_name() << ">\n";
}
#endif
