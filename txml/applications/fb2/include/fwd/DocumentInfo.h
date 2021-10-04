#ifndef FB2_DOCUMENT_INFO_H
#define FB2_DOCUMENT_INFO_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class Empty;
class DocumentInfo :
                    public txml::XMLNode<DocumentInfo, Empty>
{
public:
    using base = txml::XMLNode<DocumentInfo, Empty>;

    static constexpr const char *class_name()
    {
        return "document-info";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }

    virtual const char *name() const noexcept override;
};
} // namespace fb2
#endif //FB2_DOCUMENT_INFO_H
