#ifndef KEY_PHRASE_H
#define KEY_PHRASE_H

#include <txml/XMLNode.h>
#include <txml/XMLSerializable.h>

class TextElement;
class KeyPhrase : public XMLNode<KeyPhrase, TextElement>,
                  public XMLSerializable<KeyPhrase>,
                  public XMLFormatSerializable<KeyPhrase>
{
public:
    using base = XMLNode<KeyPhrase, TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "k";
    }

    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return TextReaderWrapper::NodeType::Element;
    };

    const char *name() const noexcept override;
    const value_t &getValue() const;

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = EmptyTracer>
    void format_serialize_impl(Formatter& out, Tracer tracer = Tracer()) const;
};

#endif //KEY_PHRASE_H
