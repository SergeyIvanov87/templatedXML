#ifndef FB2_FICTION_BOOK_HPP
#define FB2_FICTION_BOOK_HPP
#include <iostream>

#include "common/fb2/FictionBook.h"
#include "common/fb2/Description.hpp"
#include "common/fb2/body/Body.hpp"
#include "common/fb2/auxiliary/Binary.hpp"

#include "common/xml/XMLProducible.hpp"
#include "common/xml/XMLPublishing.hpp"
#include "common/xml/XMLCreator.hpp"
#include "common/xml/XMLNode.hpp"

const char *FictionBook::name() const noexcept
{
    return FictionBook::class_name();
}

template<class Tracer>
bool FictionBook::initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, depth, reader, tracer);
    return true;
}

template<class Tracer>
void FictionBook::dump(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << FictionBook::class_name() << ">";
    this->dump_all(out, tracer, no_sep);
    out << "</" << FictionBook::class_name() << ">\n";
}
#endif
