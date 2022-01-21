#ifndef FB2_AUTHOR_LAST_NAME_HPP
#define FB2_AUTHOR_LAST_NAME_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/include/fwd/LastName.h>
#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
const LastName::value_t &LastName::getValue() const
{
    auto val = base::getValue<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(LastName::class_name()) + " - no value");
    }
    return val->getValue();
}
} // namespace fb2
#endif //FB2_AUTHOR_LAST_NAME_HPP
