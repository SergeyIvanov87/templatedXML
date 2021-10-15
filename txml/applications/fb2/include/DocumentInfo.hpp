#ifndef FB2_DOCUMENT_INFO_HPP
#define FB2_DOCUMENT_INFO_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/fb2/include/fwd/DocumentInfo.h>
#include <txml/applications/fb2/include/Empty.hpp>

namespace fb2
{
const char *DocumentInfo::name() const noexcept
{
    return DocumentInfo::class_name();
}
} // namespace fb2
#endif
