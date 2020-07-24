#ifndef FICTION_BOOK_H
#define FICTION_BOOK_H

#include "common/xml/XMLNode.h"
#include "common/xml/XMLProducible.h"
#include "common/xml/XMLPublishing.h"

class Description;
class Body;
class Binary;
class FictionBook : public XMLNode<Description, Body, Binary>,
                    public XMLProducible<FictionBook>,
                    public XMLPublishing<FictionBook>
{
public:
    using base = XMLNode<Description, Body, Binary>;

    static constexpr const char *class_name()
    {
        return "FictionBook";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = Tracer<EmptyTracerImpl>>
    bool initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer = Tracer());

    template<class Tracer = Tracer<EmptyTracerImpl>>
    void dump(std::ostream &out, Tracer tracer = Tracer()) const;
};
#endif //FICTION_BOOK_H
