#ifndef FB2_BODY_HPP
#define FB2_BODY_HPP
#include <iostream>

#include "common/fb2/body/Body.h"
#include "common/fb2/body/Section.hpp"

#include "common/xml/XMLProducible.hpp"
#include "common/xml/XMLPublishing.hpp"
#include "common/xml/XMLCreator.hpp"
#include "common/xml/XMLNode.hpp"
#include "common/xml/XMLArrayContainerNode.hpp"

const char *Body::name() const noexcept
{
    return Body::class_name();
}

template<class Tracer>
bool Body::initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, depth, reader, tracer);
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
