#ifndef FB2_AUTHOR_LAST_NAME_H
#define FB2_AUTHOR_LAST_NAME_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class FB2TextElement;
class LastName : public txml::XMLNode<LastName, FB2TextElement>
{
public:
    using base = txml::XMLNode<LastName, FB2TextElement>;
    using value_t = std::string;

    static constexpr std::string_view class_name()
    {
        return "last-name";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const value_t &value() const;
};
} // namespace fb2
#endif //FB2_AUTHOR_LAST_NAME_H
