#ifndef FB2_DESCRIPTION_HPP
#define FB2_DESCRIPTION_HPP
#include <iostream>

#include "fb2/Description.h"
#include "fb2/TitleInfo.hpp"
#include "fb2/DocumentInfo.hpp"
#include "fb2/PublishInfo.hpp"

#include "XMLProducible.hpp"
#include "XMLSerializable.hpp"
#include "XMLCreator.hpp"
#include "XMLNode.hpp"

const char *Description::name() const noexcept
{
    return Description::class_name();
}

template<class Tracer>
bool Description::initialize(std::string &name, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name,  reader, tracer);
    return true;
}

template<class Tracer>
void Description::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Description::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << Description::class_name() << ">\n";
}
#endif
