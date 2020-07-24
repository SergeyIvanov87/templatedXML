#ifndef FB2_TITLE_INFO_HPP
#define FB2_TITLE_INFO_HPP
#include <iostream>

#include "common/fb2/TitleInfo.h"
#include "common/fb2/BookTitle.hpp"

#include "common/xml/XMLProducible.hpp"
#include "common/xml/XMLPublishing.hpp"
#include "common/xml/XMLCreator.hpp"
#include "common/xml/XMLNode.hpp"

const char *TitleInfo::name() const noexcept
{
    return TitleInfo::class_name();
}

template<class Tracer>
bool TitleInfo::initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, depth, reader, tracer);
    return true;
}

template<class Tracer>
void TitleInfo::dump(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << TitleInfo::class_name() << ">";
    this->dump_all(out, tracer, no_sep);
    out << "</" << TitleInfo::class_name() << ">\n";
}
#endif
