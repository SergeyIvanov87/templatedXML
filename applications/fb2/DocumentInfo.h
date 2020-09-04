#ifndef FB2_DOCUMENT_INFO_H
#define FB2_DOCUMENT_INFO_H
#include "common/xml/XMLNode.h"
#include "common/xml/XMLProducible.h"
#include "common/xml/XMLPublishing.h"

class Empty;
class DocumentInfo :
                    public XMLNode<Empty>,
                    public XMLProducible<DocumentInfo>,
                    public XMLPublishing<DocumentInfo>
{
public:
    using base = XMLNode<BookTitle>;

    static constexpr const char *class_name()
    {
        return "document-info";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    bool initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer = Tracer());

    template<class Tracer = EmptyTracer>
    void dump(std::ostream &out, Tracer tracer = Tracer()) const;
};
#endif //FB2_DOCUMENT_INFO_H
