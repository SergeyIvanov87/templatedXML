#ifndef FB2_BOOK_TITLE_HPP
#define FB2_BOOK_TITLE_HPP
#include <iostream>

#include "fb2/BookTitle.h"
#include "fb2/FB2TextElement.hpp"
#include "XMLProducible.hpp"
#include "XMLPublishing.hpp"
#include "XMLCreator.hpp"

const char *BookTitle::name() const noexcept
{
    return class_name();
}

const BookTitle::value_t &BookTitle::getValue() const
{
    auto val = base::get<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(BookTitle::class_name()) + " - no value");
    }
    return val->getValue();
}

template<class Tracer>
bool BookTitle::initialize(std::string &name, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, reader, tracer);
    return true;
}


template<class Tracer>
void BookTitle::dump(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << BookTitle::class_name() << ">";
    this->dump_all(out, tracer, no_sep);
    out << "</" << BookTitle::class_name() << ">\n";
}

#endif //FB2_BOOK_TITLE_HPP
