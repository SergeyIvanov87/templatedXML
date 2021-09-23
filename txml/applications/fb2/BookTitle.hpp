#ifndef FB2_BOOK_TITLE_HPP
#define FB2_BOOK_TITLE_HPP
#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/BookTitle.h>
#include <txml/applications/fb2/FB2TextElement.hpp>

namespace fb2
{
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
void BookTitle::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << BookTitle::class_name() << ">";
    this->serialize_elements(out, tracer, txml::no_sep);
    out << "</" << BookTitle::class_name() << ">\n";
}
} // namespace fb2
#endif //FB2_BOOK_TITLE_HPP
