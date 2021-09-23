#ifndef FB2_BOOK_TITLE_H
#define FB2_BOOK_TITLE_H

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/fwd/XMLSerializable.h>

namespace fb2
{
class FB2TextElement;
class BookTitle : public txml::XMLNode<BookTitle, FB2TextElement>,
                  public txml::XMLSerializable<BookTitle>
{
public:
    using base = txml::XMLNode<BookTitle, FB2TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "book-title";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const char *name() const noexcept override;
    const value_t &getValue() const;

    template<class Tracer = txml::EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};
} // namespace fb2
#endif //FB2_BOOK_TITLE_H
