#ifndef FB2_PARAGRAPH_H
#define FB2_PARAGRAPH_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class FB2TextElement;
class Paragraph : public txml::XMLNode<Paragraph, FB2TextElement>
{
public:
    using base = txml::XMLNode<Paragraph, FB2TextElement>;
    using base::base;
    using value_t = std::string;

    static constexpr std::string_view class_name()
    {
        return "p";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const value_t &value() const;
};
} // namespace fb2
#endif //FB2_PARAGRAPH_H
