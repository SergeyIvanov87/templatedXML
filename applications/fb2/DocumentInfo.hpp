#ifndef FB2_DOCUMENT_INFO_HPP
#define FB2_DOCUMENT_INFO_HPP
#include <iostream>

#include "common/fb2/DocumentInfo.h"
#include "common/fb2/Empty.hpp"

#include "common/xml/XMLProducible.hpp"
#include "common/xml/XMLPublishing.hpp"
#include "common/xml/XMLCreator.hpp"
#include "common/xml/XMLNode.hpp"

const char *DocumentInfo::name() const noexcept
{
    return DocumentInfo::class_name();
}

template<class Tracer>
bool DocumentInfo::initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, depth, reader, tracer);
    return true;
}

template<class Tracer>
void DocumentInfo::dump(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << DocumentInfo::class_name() << ">";
    this->dump_all(out, tracer, no_sep);
    out << "</" << DocumentInfo::class_name() << ">\n";
}
#endif
