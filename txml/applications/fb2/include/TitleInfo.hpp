#ifndef FB2_TITLE_INFO_HPP
#define FB2_TITLE_INFO_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/fb2/include/fwd/TitleInfo.h>
#include <txml/applications/fb2/include/BookTitle.hpp>

namespace fb2
{
const char *TitleInfo::name() const noexcept
{
    return TitleInfo::class_name();
}
} // namespace fb2
#endif
