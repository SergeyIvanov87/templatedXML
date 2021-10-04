#ifndef FB2_BODY_H
#define FB2_BODY_H

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>
#include <txml/include/fwd/XMLArrayContainerNode.h>

namespace fb2
{
class Section;
class Body : public txml::XMLNode<Body, txml::XMLArrayContainerNode<Section>>,
             public txml::XMLSerializable<Body>,
             public txml::XMLFormatDeserializable<Body>,
             public txml::XMLSchemaSerializable<Body>
{
public:
    using base = txml::XMLNode<Body, txml::XMLArrayContainerNode<Section>>;

    static constexpr const char *class_name()
    {
        return "body";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = txml::EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_deserialize_impl(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_impl(Formatter& out, Tracer tracer = Tracer());
};
} // namespace fb2
#endif //FB2_BODY_H
