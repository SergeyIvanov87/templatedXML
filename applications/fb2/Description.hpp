#ifndef FB2_DESCRIPTION_HPP
#define FB2_DESCRIPTION_HPP
#include <iostream>

#include "common/fb2/Description.h"
#include "common/fb2/TitleInfo.hpp"
#include "common/fb2/DocumentInfo.hpp"
#include "common/fb2/PublishInfo.hpp"

#include "common/xml/XMLProducible.hpp"
#include "common/xml/XMLPublishing.hpp"
#include "common/xml/XMLCreator.hpp"
#include "common/xml/XMLNode.hpp"

const char *Description::name() const noexcept
{
    return Description::class_name();
}

template<class Tracer>
bool Description::initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, depth, reader, tracer);
    return true;
}

template<class Tracer>
void Description::dump(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Description::class_name() << ">";
    this->dump_all(out, tracer, no_sep);
    out << "</" << Description::class_name() << ">\n";
}
#endif
