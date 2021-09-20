#ifndef XDXF_ARTICLE_H
#define XDXF_ARTICLE_H

#include <txml/XMLNode.h>
#include <txml/XMLSerializable.h>

class KeyPhrase;
class Comment;
class Transcription;
class TextElement;
class XDXFArticle : public XMLNode<XDXFArticle, KeyPhrase, Comment, Transcription, TextElement>,
                    public XMLSerializable<XDXFArticle>,
                    public XMLFormatSerializable<XDXFArticle>
{
public:
    using base = XMLNode<XDXFArticle, KeyPhrase, Comment, Transcription, TextElement>;

    static constexpr const char *class_name()
    {
        return "ar";
    }

    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return TextReaderWrapper::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = EmptyTracer>
    void format_serialize_impl(Formatter& out, Tracer tracer = Tracer()) const;
};
#endif //XDXF_ARTICLE_H
