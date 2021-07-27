#ifndef FB2_DOCUMENT_INFO_H
#define FB2_DOCUMENT_INFO_H
#include "XMLNode.h"
#include "XMLSerializable.h"

class Empty;
class DocumentInfo :
                    public XMLNode<DocumentInfo, Empty>,
                    public XMLSerializable<DocumentInfo>
{
public:
    using base = XMLNode<DocumentInfo, BookTitle>;

    static constexpr const char *class_name()
    {
        return "document-info";
    }

    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return TextReaderWrapper::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};
#endif //FB2_DOCUMENT_INFO_H
