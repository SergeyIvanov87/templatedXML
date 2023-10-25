#ifndef FB2_BOOK_TITLE_HPP
#define FB2_BOOK_TITLE_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/include/fwd/BookTitle.h>
#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
inline const BookTitle::value_t &BookTitle::value() const
{
    const auto& val = base::node<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(BookTitle::class_name()) + " - no value");
    }
    return val->value();
}
} // namespace fb2
#endif //FB2_BOOK_TITLE_HPP
