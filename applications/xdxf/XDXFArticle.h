#ifndef XDXF_ARTICLE_H
#define XDXF_ARTICLE_H
#include "XMLNode.h"
#include "XMLProducible.h"
#include "XMLPublishing.h"

class KeyPhrase;
class Comment;
class Transcription;
class TextElement;
class XDXFArticle : public XMLNode<KeyPhrase, Comment, Transcription, TextElement>,
                    public XMLProducible<XDXFArticle>,
                    public XMLPublishing<XDXFArticle>,
                    public XMLFormattingPublishing<XDXFArticle>
{
public:
    using base = XMLNode<KeyPhrase, Comment, Transcription, TextElement>;

    static constexpr const char *class_name()
    {
        return "ar";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    bool initialize(std::string &name, xmlpp::TextReader &reader, Tracer tracer = Tracer());

    template<class Tracer = EmptyTracer>
    void dump(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = EmptyTracer>
    void format_dump(Formatter& out, Tracer tracer = Tracer()) const;
};
#endif //XDXF_ARTICLE_H
