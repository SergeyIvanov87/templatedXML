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

    static constexpr const char* class_name()
    {
        return "binary";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const char *name() const noexcept override;
    const value_t &getValue() const;
};
} // namespace fb2
#endif //BINARY_H
