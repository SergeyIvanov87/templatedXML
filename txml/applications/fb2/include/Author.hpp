#ifndef FB2_DOCUMENT_INFO_AUTHOR_HPP
#define FB2_DOCUMENT_INFO_AUTHOR_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/fb2/include/fwd/Author.h>
#include <txml/applications/fb2/include/FirstName.hpp>
#include <txml/applications/fb2/include/MiddleName.hpp>
#include <txml/applications/fb2/include/LastName.hpp>
#include <txml/applications/fb2/include/NickName.hpp>

namespace fb2
{
const char *Author::name() const noexcept
{
    return Author::class_name();
}
} // namespace fb2
#endif
