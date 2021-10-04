#ifndef XDXF_ARTICLE_H
#define XDXF_ARTICLE_H

#include <ostream>

#include <txml/include/fwd/XMLNode.h>

namespace xdxf
{
class KeyPhrase;
class Comment;
class Transcription;
class TextElement;
class XDXFArticle : public txml::XMLNode<XDXFArticle, KeyPhrase, Comment, Transcription, TextElement>
{
public:
    using base = txml::XMLNode<XDXFArticle, KeyPhrase, Comment, Transcription, TextElement>;

    static constexpr const char *class_name()
    {
        return "ar";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }

    virtual const char *name() const noexcept override;
};
} // namespace xdxf
#endif //XDXF_ARTICLE_H
