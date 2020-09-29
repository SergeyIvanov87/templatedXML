#ifndef KEY_PHRASE_H
#define KEY_PHRASE_H

#include "XMLNode.h"
#include "XMLProducible.h"
#include "XMLSerializable.h"

class TextElement;
class KeyPhrase : public XMLNode<TextElement>,
                  public XMLProducible<KeyPhrase>,
                  public XMLSerializable<KeyPhrase>,
                  public XMLFormatSerializable<KeyPhrase>
{
public:
    using base = XMLNode<TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "k";
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
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = EmptyTracer>
    void format_serialize_impl(Formatter& out, Tracer tracer = Tracer()) const;
};

#endif //KEY_PHRASE_H
