#ifndef FB2_AUTHOR_MIDDLE_NAME_HPP
#define FB2_AUTHOR_MIDDLE_NAME_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/include/fwd/MiddleName.h>
#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
const char *MiddleName::name() const noexcept
{
    return class_name();
}

const MiddleName::value_t &MiddleName::getValue() const
{
    auto val = base::getValue<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(MiddleName::class_name()) + " - no value");
    }
    return val->getValue();
}
} // namespace fb2
#endif //FB2_AUTHOR_MIDDLE_NAME_HPP
