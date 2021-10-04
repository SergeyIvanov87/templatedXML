#ifndef FB2_BODY_H
#define FB2_BODY_H

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/fwd/XMLArrayContainerNode.h>

namespace fb2
{
class Section;
class Body : public txml::XMLNode<Body, txml::XMLArrayContainerNode<Section>>
{
public:
    using base = txml::XMLNode<Body, txml::XMLArrayContainerNode<Section>>;

    static constexpr const char *class_name()
    {
        return "body";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }

    virtual const char *name() const noexcept override;
};
} // namespace fb2
#endif //FB2_BODY_H
