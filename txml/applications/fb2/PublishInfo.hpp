#ifndef FB2_PUBLISH_INFO_HPP
#define FB2_PUBLISH_INFO_HPP
#include <iostream>

#include "fb2/PublishInfo.h"
#include "fb2/Empty.hpp"

#include "XMLProducible.hpp"
#include "XMLSerializable.hpp"
#include "XMLCreator.hpp"
#include "XMLNode.hpp"

const char *PublishInfo::name() const noexcept
{
    return PublishInfo::class_name();
}

template<class Tracer>
bool PublishInfo::initialize(std::string &name, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, reader, tracer);
    return true;
}

template<class Tracer>
void PublishInfo::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << PublishInfo::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << PublishInfo::class_name() << ">\n";
}
#endif
