#ifndef KEY_PHRASE_H
#define KEY_PHRASE_H

#include <ostream>
#include <string>

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

namespace xdxf
{
class TextElement;
class KeyPhrase : public txml::XMLNode<KeyPhrase, TextElement>,
                  public txml::XMLSerializable<KeyPhrase>,
                  public txml::XMLFormatSerializable<KeyPhrase>,
                public txml::XMLSchemaSerializable<KeyPhrase>

{
public:
    using base = txml::XMLNode<KeyPhrase, TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "k";
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
    void format_serialize_impl(Formatter& out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_impl(Formatter& out, Tracer tracer = Tracer());
};
} // namespace xdxf
#endif //KEY_PHRASE_H
