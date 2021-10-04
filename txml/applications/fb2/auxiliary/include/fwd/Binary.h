#ifndef BINARY_H
#define BINARY_H

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

namespace fb2
{
class Empty;
class Binary : public txml::XMLNode<Binary, Empty>,
               public txml::XMLSerializable<Binary>,
               public txml::XMLFormatDeserializable<Binary>,
               public txml::XMLSchemaSerializable<Binary>
{
public:
    using base = txml::XMLNode<Binary, Empty>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "binary";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

    const char *name() const noexcept override;
    const value_t &getValue() const;

    template<class Tracer = txml::EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_deserialize_impl(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_impl(Formatter& out, Tracer tracer = Tracer());
};
} // namespace fb2
#endif //BINARY_H
