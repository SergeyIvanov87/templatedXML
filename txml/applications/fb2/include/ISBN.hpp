#ifndef FB2_PUBLISH_INFO_ISBN_HPP
#define FB2_PUBLISH_INFO_ISBN_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/include/fwd/ISBN.h>
#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
const ISBN::value_t &ISBN::value() const
{
    const auto& val = base::node<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(ISBN::class_name()) + " - no value");
    }
    return val->value();
}
} // namespace fb2
#endif //FB2_PUBLISH_INFO_ISBN_HPP
