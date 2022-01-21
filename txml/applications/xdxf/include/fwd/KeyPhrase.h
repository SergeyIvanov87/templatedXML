#ifndef KEY_PHRASE_H
#define KEY_PHRASE_H

#include <ostream>
#include <string>

#include <txml/include/fwd/XMLNode.h>

namespace xdxf
{
class TextElement;
class KeyPhrase : public txml::XMLNode<KeyPhrase, TextElement>
{
public:
    using base = txml::XMLNode<KeyPhrase, TextElement>;
    using value_t = std::string;

    static constexpr std::string_view class_name()
    {
        return "k";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const value_t &getValue() const;
};
} // namespace xdxf
#endif //KEY_PHRASE_H
