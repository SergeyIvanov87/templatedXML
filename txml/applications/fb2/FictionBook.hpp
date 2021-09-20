#ifndef FB2_FICTION_BOOK_HPP
#define FB2_FICTION_BOOK_HPP
#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/fb2/FictionBook.h>
#include <txml/applications/fb2/Description.hpp>
#include <txml/applications/fb2/body/Body.hpp>
#include <txml/applications/fb2/auxiliary/Binary.hpp>

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
