#ifndef XDXF_ARTICLE_HPP
#define XDXF_ARTICLE_HPP

#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/xdxf/include/fwd/XDXFArticle.h>
#include <txml/applications/xdxf/include/KeyPhrase.hpp>
#include <txml/applications/xdxf/include/Comment.hpp>
#include <txml/applications/xdxf/include/Transcription.hpp>
#include <txml/applications/xdxf/include/TextElement.hpp>

namespace xdxf
{
const char *XDXFArticle::name() const noexcept
{
    return XDXFArticle::class_name();
}
} // namespace xdxf
#endif
