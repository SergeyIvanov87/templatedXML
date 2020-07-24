#ifndef FB2_DESCRIPTION_H
#define FB2_DESCRIPTION_H
#include "common/xml/XMLNode.h"
#include "common/xml/XMLProducible.h"
#include "common/xml/XMLPublishing.h"

class TitleInfo;
class DocumentInfo;
class PublishInfo;
class Description : public XMLNode<TitleInfo, DocumentInfo, PublishInfo>,
                    public XMLProducible<Description>,
                    public XMLPublishing<Description>
{
public:
    using base = XMLNode<TitleInfo, DocumentInfo, PublishInfo>;

    static constexpr const char *class_name()
    {
        return "description";
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
#endif //FB2_DESCRIPTION_H
