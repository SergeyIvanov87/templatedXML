#ifndef TRANSCRIPTION_H
#define TRANSCRIPTION_H

#include "XMLNode.h"
#include "XMLSerializable.h"

class TextElement;
class Transcription : public XMLNode<Transcription, TextElement>,
                      public XMLSerializable<Transcription>,
                      public XMLFormatSerializable<Transcription>
{
public:
    using base = XMLNode<Transcription, TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "tr";
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

#endif //TRANSCRIPTION_H
