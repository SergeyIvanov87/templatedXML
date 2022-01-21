#ifndef FB2_TITLE_INFO_H
#define FB2_TITLE_INFO_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class BookTitle;
class Genre;
class Language;
class TitleInfo : public txml::XMLNode<TitleInfo, BookTitle, Genre, Language>
{
public:
    using base = txml::XMLNode<TitleInfo, BookTitle, Genre, Language>;

    static constexpr std::string_view class_name()
    {
        return "title-info";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }
};
} // namespace fb2
#endif //FB2_TITLE_INFO_H
