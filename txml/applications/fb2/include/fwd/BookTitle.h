#ifndef FB2_BOOK_TITLE_H
#define FB2_BOOK_TITLE_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class FB2TextElement;
class BookTitle : public txml::XMLNode<BookTitle, FB2TextElement>
{
public:
    using base = txml::XMLNode<BookTitle, FB2TextElement>;
    using value_t = std::string;

    static constexpr std::string_view class_name()
    {
        return "book-title";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const value_t &value() const;
};
} // namespace fb2
#endif //FB2_BOOK_TITLE_H
