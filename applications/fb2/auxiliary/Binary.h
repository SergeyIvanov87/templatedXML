#ifndef BINARY_H
#define BINARY_H

#include "XMLNode.h"
#include "XMLProducible.h"
#include "XMLPublishing.h"

class Empty;
class Binary : public XMLNode<Empty>,
                  public XMLProducible<Binary>,
                  public XMLPublishing<Binary>
{
public:
    using base = XMLNode<Empty>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "binary";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Element;
    };

    const char *name() const noexcept override;
    const value_t &getValue() const;

    template<class Tracer = EmptyTracer>
    bool initialize(std::string &name, xmlpp::TextReader &reader, Tracer tracer = Tracer());

    template<class Tracer = EmptyTracer>
    void dump(std::ostream &out, Tracer tracer = Tracer()) const;
};

#endif //BINARY_H
