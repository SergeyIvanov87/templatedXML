#ifndef FB2_AUTHOR_NICKNAME_H
#define FB2_AUTHOR_NICKNAME_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class FB2TextElement;
class NickName : public txml::XMLNode<NickName, FB2TextElement>
{
public:
    using base = txml::XMLNode<NickName, FB2TextElement>;
    using value_t = std::string;

    static constexpr std::string_view class_name()
    {
        return "nickname";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const value_t &getValue() const;
};
} // namespace fb2
#endif //FB2_AUTHOR_NICKNAME_H
