#ifndef FB2_TITLE_INFO_LANGUAGE_HPP
#define FB2_TITLE_INFO_LANGUAGE_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/include/fwd/Language.h>
#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
const char *Language::name() const noexcept
{
    return class_name();
}

const Language::value_t &Language::getValue() const
{
    auto val = base::getValue<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(Language::class_name()) + " - no value");
    }
    return val->getValue();
}
} // namespace fb2
#endif //FB2_TITLE_INFO_LANGUAGE_HPP
