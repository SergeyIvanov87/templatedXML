#ifndef FB2_AUTHOR_NICKNAME_HPP
#define FB2_AUTHOR_NICKNAME_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/include/fwd/NickName.h>
#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
const NickName::value_t &NickName::value() const
{
    const auto& val = base::node<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(NickName::class_name()) + " - no value");
    }
    return val->value();
}
} // namespace fb2
#endif //FB2_AUTHOR_NICKNAME_HPP
