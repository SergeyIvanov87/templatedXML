#ifndef FB2_PUBLISH_INFO_PUBLISHER_HPP
#define FB2_PUBLISH_INFO_PUBLISHER_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/include/fwd/Publisher.h>
#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
const char *Publisher::name() const noexcept
{
    return class_name();
}

const Publisher::value_t &Publisher::getValue() const
{
    auto val = base::getValue<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(Publisher::class_name()) + " - no value");
    }
    return val->getValue();
}
} // namespace fb2
#endif //FB2_PUBLISH_INFO_PUBLISHER_HPP
