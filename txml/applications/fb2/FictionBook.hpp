#ifndef FB2_FICTION_BOOK_HPP
#define FB2_FICTION_BOOK_HPP
#include <iostream>

#include "fb2/FictionBook.h"
#include "fb2/Description.hpp"
#include "fb2/body/Body.hpp"
#include "fb2/auxiliary/Binary.hpp"

#include "XMLProducible.hpp"
#include "XMLPublishing.hpp"
#include "XMLCreator.hpp"
#include "XMLNode.hpp"

const char *FictionBook::name() const noexcept
{
    return FictionBook::class_name();
}

template<class Tracer>
bool FictionBook::initialize(std::string &name, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, reader, tracer);
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
