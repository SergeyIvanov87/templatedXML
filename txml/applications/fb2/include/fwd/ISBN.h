#ifndef FB2_PUBLISH_INFO_ISBN_H
#define FB2_PUBLISH_INFO_ISBN_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class FB2TextElement;
class ISBN : public txml::XMLNode<ISBN, FB2TextElement>
{
public:
    using base = txml::XMLNode<ISBN, FB2TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "isbn";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const char *name() const noexcept override;
    const value_t &getValue() const;
};
} // namespace fb2
#endif //FB2_PUBLISH_INFO_ISBN_H
