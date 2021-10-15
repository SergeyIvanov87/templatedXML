#ifndef FB2_DESCRIPTION_HPP
#define FB2_DESCRIPTION_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/fb2/include/fwd/Description.h>
#include <txml/applications/fb2/include/TitleInfo.hpp>
#include <txml/applications/fb2/include/DocumentInfo.hpp>
#include <txml/applications/fb2/include/PublishInfo.hpp>

namespace fb2
{
const char *Description::name() const noexcept
{
    return Description::class_name();
}
} // namespace fb2
#endif
