#ifndef BINARY_H
#define BINARY_H

#include "XMLNode.h"
#include "XMLSerializable.h"

class Empty;
class Binary : public XMLNode<Binary, Empty>,
                  public XMLSerializable<Binary>
{
public:
    using base = XMLNode<Binary, Empty>;
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
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};

#endif //BINARY_H
