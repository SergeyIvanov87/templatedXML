#ifndef FB2_PUBLISH_INFO_HPP
#define FB2_PUBLISH_INFO_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/fb2/include/fwd/PublishInfo.h>
#include <txml/applications/fb2/include/Empty.hpp>

namespace fb2
{
const char *PublishInfo::name() const noexcept
{
    return PublishInfo::class_name();
}
} // namespace fb2
#endif // FB2_PUBLISH_INFO_HPP
