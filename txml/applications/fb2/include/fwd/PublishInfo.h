#ifndef FB2_PUBLISH_INFO_H
#define FB2_PUBLISH_INFO_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class Publisher;
class ISBN;
class PublishInfo : public txml::XMLNode<PublishInfo, Publisher, ISBN>
{
public:
    using base = txml::XMLNode<PublishInfo, Publisher, ISBN>;

    static constexpr std::string_view class_name()
    {
        return "publish-info";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }
};
} // namespace fb2
#endif //FB2_PUBLISH_INFO_H
