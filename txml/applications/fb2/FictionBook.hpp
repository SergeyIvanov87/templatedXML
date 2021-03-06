#ifndef FB2_FICTION_BOOK_HPP
#define FB2_FICTION_BOOK_HPP
#include <iostream>

#include "fb2/FictionBook.h"
#include "fb2/Description.hpp"
#include "fb2/body/Body.hpp"
#include "fb2/auxiliary/Binary.hpp"

#include "XMLSerializable.hpp"
#include "XMLCreator.hpp"
#include "XMLNode.hpp"

const char *FictionBook::name() const noexcept
{
    return FictionBook::class_name();
}

template<class Tracer>
void FictionBook::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << FictionBook::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << FictionBook::class_name() << ">\n";
}
#endif
