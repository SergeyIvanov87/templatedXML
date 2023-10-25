#ifndef FB2_PUBLISH_INFO_PUBLISHER_HPP
#define FB2_PUBLISH_INFO_PUBLISHER_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/include/fwd/Publisher.h>
#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
inline const Publisher::value_t &Publisher::value() const
{
    const auto& val = base::node<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(Publisher::class_name()) + " - no value");
    }
    return val->value();
}
} // namespace fb2
#endif //FB2_PUBLISH_INFO_PUBLISHER_HPP
