#ifndef FB2_DOCUMENT_INFO_H
#define FB2_DOCUMENT_INFO_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class Author;
class DocumentInfo: public txml::XMLNode<DocumentInfo, Author>
{
public:
    using base_t = txml::XMLNode<DocumentInfo, Author>;

    static constexpr std::string_view class_name()
    {
        return "document-info";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }
};
} // namespace fb2
#endif //FB2_DOCUMENT_INFO_H
