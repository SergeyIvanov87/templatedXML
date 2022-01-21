#ifndef TRANSCRIPTION_H
#define TRANSCRIPTION_H

#include <ostream>
#include <string>

#include <txml/include/fwd/XMLNode.h>

namespace xdxf
{
class TextElement;
class Transcription : public txml::XMLNode<Transcription, TextElement>
{
public:
    using base = txml::XMLNode<Transcription, TextElement>;
    using value_t = std::string;

    static constexpr std::string_view class_name()
    {
        return "tr";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const value_t &getValue() const;
};
} // namespace xdxf
#endif //TRANSCRIPTION_H
