#ifndef FB2_SECTION_HPP
#define FB2_SECTION_HPP
#include <iostream>

#include "common/fb2/body/Section.h"
#include "common/fb2/common/Paragraph.hpp"
#include "common/xml/XMLProducible.hpp"
#include "common/xml/XMLPublishing.hpp"
#include "common/xml/XMLCreator.hpp"
#include "common/xml/XMLNode.hpp"
#include "common/xml/XMLArrayContainerNode.hpp"


const char *Section::name() const noexcept
{
    return Section::class_name();
}

template<class Tracer>
bool Section::initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, depth, reader, tracer);
    return true;
}

template<class Tracer>
void Section::dump(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Section::class_name() << ">";
    this->dump_all(out, tracer, no_sep);
    out << "</" << Section::class_name() << ">\n";
}
#endif
