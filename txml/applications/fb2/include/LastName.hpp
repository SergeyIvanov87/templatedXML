#ifndef FB2_AUTHOR_LAST_NAME_HPP
#define FB2_AUTHOR_LAST_NAME_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/include/fwd/LastName.h>
#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
inline const LastName::value_t &LastName::value() const
{
    const auto& val = base::node<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(LastName::class_name()) + " - no value");
    }
    return val->value();
}
} // namespace fb2
#endif //FB2_AUTHOR_LAST_NAME_HPP
