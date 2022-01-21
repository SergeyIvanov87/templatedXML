#ifndef FB2_TITLE_INFO_LANGUAGE_H
#define FB2_TITLE_INFO_LANGUAGE_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class FB2TextElement;
class Language : public txml::XMLNode<Language, FB2TextElement>
{
public:
    using base = txml::XMLNode<Language, FB2TextElement>;
    using value_t = std::string;

    static constexpr std::string_view class_name()
    {
        return "lang";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const value_t &getValue() const;
};
} // namespace fb2
#endif //FB2_TITLE_INFO_LANGUAGE_H