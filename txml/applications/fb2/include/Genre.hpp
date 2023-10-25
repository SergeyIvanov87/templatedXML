#ifndef FB2_TITLE_INFO_GENRE_HPP
#define FB2_TITLE_INFO_GENRE_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/include/fwd/Genre.h>
#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
inline const Genre::value_t &Genre::value() const
{
    const auto& val = base::node<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(Genre::class_name()) + " - no value");
    }
    return val->value();
}
} // namespace fb2
#endif //FB2_TITLE_INFO_GENRE_HPP
