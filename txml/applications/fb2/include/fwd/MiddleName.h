#ifndef FB2_AUTHOR_MIDDLE_NAME_H
#define FB2_AUTHOR_MIDDLE_NAME_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class FB2TextElement;
class MiddleName : public txml::XMLNode<MiddleName, FB2TextElement>
{
public:
    using base = txml::XMLNode<MiddleName, FB2TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "middle-name";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const char *name() const noexcept override;
    const value_t &getValue() const;
};
} // namespace fb2
#endif //FB2_AUTHOR_MIDDLE_NAME_H
