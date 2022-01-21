#ifndef FB2_TITLE_INFO_GENRE_H
#define FB2_TITLE_INFO_GENRE_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class FB2TextElement;
class Genre : public txml::XMLNode<Genre, FB2TextElement>
{
public:
    using base = txml::XMLNode<Genre, FB2TextElement>;
    using value_t = std::string;

    static constexpr std::string_view class_name()
    {
        return "genre";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const value_t &getValue() const;
};
} // namespace fb2
#endif //FB2_TITLE_INFO_GENRE_H
