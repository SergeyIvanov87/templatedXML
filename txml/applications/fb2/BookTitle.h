#ifndef FB2_BOOK_TITLE_H
#define FB2_BOOK_TITLE_H

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/fwd/XMLSerializable.h>

class FB2TextElement;
class BookTitle : public XMLNode<BookTitle, FB2TextElement>,
                  public XMLSerializable<BookTitle>
{
public:
    using base = XMLNode<BookTitle, FB2TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "book-title";
    }

    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return TextReaderWrapper::NodeType::Element;
    };

    const char *name() const noexcept override;
    const value_t &getValue() const;

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};

#endif //FB2_BOOK_TITLE_H
