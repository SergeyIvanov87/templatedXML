#ifndef FB2_TITLE_INFO_LANGUAGE_HPP
#define FB2_TITLE_INFO_LANGUAGE_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/include/fwd/Language.h>
#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
const Language::value_t &Language::value() const
{
    const auto& val = base::node<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(Language::class_name()) + " - no value");
    }
    return val->value();
}
} // namespace fb2
#endif //FB2_TITLE_INFO_LANGUAGE_HPP
