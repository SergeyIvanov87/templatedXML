#ifndef FB2_PARAGRAPH_H
#define FB2_PARAGRAPH_H

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

namespace fb2
{
class FB2TextElement;
class Paragraph : public txml::XMLNode<Paragraph, FB2TextElement>,
                  public txml::XMLSerializable<Paragraph>,
                  public txml::XMLFormatDeserializable<Paragraph>,
                  public txml::XMLSchemaSerializable<Paragraph>
{
public:
    using base = txml::XMLNode<Paragraph, FB2TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "p";
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
#endif //FB2_PARAGRAPH_H
