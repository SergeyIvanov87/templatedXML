#ifndef FB2_AUTHOR_FIRST_NAME_HPP
#define FB2_AUTHOR_FIRST_NAME_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/include/fwd/FirstName.h>
#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
inline const FirstName::value_t &FirstName::value() const
{
    const auto& val = base::node<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(FirstName::class_name()) + " - no value");
    }
    return val->value();
}
} // namespace fb2
#endif //FB2_AUTHOR_FIRST_NAME_HPP
