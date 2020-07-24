#ifndef FB2_TITLE_INFO_H
#define FB2_TITLE_INFO_H
#include "common/xml/XMLNode.h"
#include "common/xml/XMLProducible.h"
#include "common/xml/XMLPublishing.h"

class BookTitle;
class TitleInfo : public XMLNode<BookTitle>,
                    public XMLProducible<TitleInfo>,
                    public XMLPublishing<TitleInfo>
{
public:
    using base = XMLNode<BookTitle>;

    static constexpr const char *class_name()
    {
        return "title-info";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = Tracer<EmptyTracerImpl>>
    bool initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer = Tracer());

    template<class Tracer = Tracer<EmptyTracerImpl>>
    void dump(std::ostream &out, Tracer tracer = Tracer()) const;
};
#endif //FB2_TITLE_INFO_H
