#ifndef FB2_DESCRIPTION_H
#define FB2_DESCRIPTION_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class TitleInfo;
class DocumentInfo;
class PublishInfo;
class Description : public txml::XMLNode<Description, TitleInfo, DocumentInfo, PublishInfo>
{
public:
    using base_t = txml::XMLNode<Description, TitleInfo, DocumentInfo, PublishInfo>;

    static constexpr std::string_view class_name()
    {
        return "description";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }
};
} // namespace fb2
#endif //FB2_DESCRIPTION_H
