#ifndef FB2_PUBLISH_INFO_H
#define FB2_PUBLISH_INFO_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class Empty;
class PublishInfo : public txml::XMLNode<PublishInfo, Empty>
{
public:
    using base = txml::XMLNode<PublishInfo, Empty>;

    static constexpr const char *class_name()
    {
        return "publish-info";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }

    virtual const char *name() const noexcept override;
};
} // namespace fb2
#endif //FB2_PUBLISH_INFO_H
