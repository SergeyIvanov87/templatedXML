#ifndef FB2_PUBLISH_INFO_HPP
#define FB2_PUBLISH_INFO_HPP
#include <iostream>

#include "common/fb2/PublishInfo.h"
#include "common/fb2/Empty.hpp"

#include "common/xml/XMLProducible.hpp"
#include "common/xml/XMLPublishing.hpp"
#include "common/xml/XMLCreator.hpp"
#include "common/xml/XMLNode.hpp"

const char *PublishInfo::name() const noexcept
{
    return PublishInfo::class_name();
}

template<class Tracer>
bool PublishInfo::initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, depth, reader, tracer);
    return true;
}

template<class Tracer>
void PublishInfo::dump(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << PublishInfo::class_name() << ">";
    this->dump_all(out, tracer, no_sep);
    out << "</" << PublishInfo::class_name() << ">\n";
}
#endif
