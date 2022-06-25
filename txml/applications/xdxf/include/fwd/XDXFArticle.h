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
    using base_t = txml::XMLNode<XDXFArticle, KeyPhrase, Comment, Transcription, TextElement>;

    static constexpr std::string_view class_name()
    {
        return "ar";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }
};
} // namespace xdxf
#endif //XDXF_ARTICLE_H
