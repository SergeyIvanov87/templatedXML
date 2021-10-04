#ifndef FB2_BODY_HPP
#define FB2_BODY_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLNode.hpp>
#include <txml/include/XMLArrayContainerNode.hpp>

#include <txml/applications/fb2/body/fb2_body_fwd.h>


namespace fb2
{
const char *Body::name() const noexcept
{
    return Body::class_name();
}
} // namespace fb2
#endif
