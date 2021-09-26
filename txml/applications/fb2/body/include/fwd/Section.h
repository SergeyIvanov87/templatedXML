#ifndef FB2_SECTION_H
#define FB2_SECTION_H

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLArrayContainerNode.h>

namespace fb2
{
class Paragraph;
class Section : public txml::XMLNode<Section, txml::XMLArrayContainerNode<Paragraph>>,
                public txml::XMLSerializable<Section>,
                public txml::XMLSchemaSerializable<Section>
{
public:
    using base = txml::XMLNode<Section>;

    static constexpr const char *class_name()
    {
        return "section";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = txml::EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_impl(Formatter& out, Tracer tracer = Tracer());
};
} // namespace fb2
#endif //FB2_SECTION_H
