#ifndef XDXF_ARTICLE_H
#define XDXF_ARTICLE_H

#include <ostream>

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

namespace xdxf
{
class KeyPhrase;
class Comment;
class Transcription;
class TextElement;
class XDXFArticle : public txml::XMLNode<XDXFArticle, KeyPhrase, Comment, Transcription, TextElement>,
                    public txml::XMLSerializable<XDXFArticle>,
                    public txml::XMLFormatSerializable<XDXFArticle>,
                    public txml::XMLSchemaSerializable<XDXFArticle>
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

    template<class Tracer = txml::EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_serialize_impl(Formatter& out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_impl(Formatter& out, Tracer tracer = Tracer());
};
} // namespace xdxf
#endif //XDXF_ARTICLE_H
