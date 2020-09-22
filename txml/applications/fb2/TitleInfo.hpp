#ifndef FB2_TITLE_INFO_HPP
#define FB2_TITLE_INFO_HPP
#include <iostream>

#include "fb2/TitleInfo.h"
#include "fb2/BookTitle.hpp"

#include "XMLProducible.hpp"
#include "XMLPublishing.hpp"
#include "XMLCreator.hpp"
#include "XMLNode.hpp"

const char *TitleInfo::name() const noexcept
{
    return TitleInfo::class_name();
}

template<class Tracer>
bool TitleInfo::initialize(std::string &name, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, reader, tracer);
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
