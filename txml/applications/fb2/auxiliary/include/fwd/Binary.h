#ifndef BINARY_H
#define BINARY_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class Empty;
class Binary : public txml::XMLNode<Binary, Empty>
{
public:
    using base = txml::XMLNode<Binary, Empty>;
    using value_t = std::string;

    static constexpr std::string_view class_name()
    {
        return "binary";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const value_t &value() const;
};
} // namespace fb2
#endif //BINARY_H
