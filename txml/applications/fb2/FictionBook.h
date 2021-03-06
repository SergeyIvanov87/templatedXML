#ifndef FICTION_BOOK_H
#define FICTION_BOOK_H

#include "XMLNode.h"
#include "XMLSerializable.h"

class Description;
class Body;
class Binary;
class FictionBook : public XMLNode<FictionBook, Description, Body, Binary>,
                    public XMLSerializable<FictionBook>
{
public:
    using base = XMLNode<FictionBook, Description, Body, Binary>;

    static constexpr const char *class_name()
    {
        return "FictionBook";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};
#endif //FICTION_BOOK_H
