#ifndef FB2_BOOK_TITLE_H
#define FB2_BOOK_TITLE_H

#include "common/xml/XMLNode.h"
#include "common/xml/XMLProducible.h"
#include "common/xml/XMLPublishing.h"

class FB2TextElement;
class BookTitle : public XMLNode<FB2TextElement>,
                  public XMLProducible<BookTitle>,
                  public XMLPublishing<BookTitle>
{
public:
    using base = XMLNode<FB2TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "book-title";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Element;
    };

    const char *name() const noexcept override;
    const value_t &getValue() const;

    template<class Tracer = EmptyTracer>
    bool initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer = Tracer());

    template<class Tracer = EmptyTracer>
    void dump(std::ostream &out, Tracer tracer = Tracer()) const;
};

#endif //FB2_BOOK_TITLE_H
