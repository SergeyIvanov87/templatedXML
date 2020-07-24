#ifndef TRANSCRIPTION_H
#define TRANSCRIPTION_H

#include "common/xml/XMLNode.h"
#include "common/xml/XMLProducible.h"
#include "common/xml/XMLPublishing.h"

class TextElement;
class Transcription : public XMLNode<TextElement>,
                      public XMLProducible<Transcription>,
                      public XMLPublishing<Transcription>,
                      public XMLFormattingPublishing<Transcription>
{
public:
    using base = XMLNode<TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "tr";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Element;
    };

    const char *name() const noexcept override;
    const value_t &getValue() const;

    template<class Tracer = Tracer<EmptyTracerImpl>>
    bool initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer = Tracer());

    template<class Tracer = Tracer<EmptyTracerImpl>>
    void dump(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = Tracer<EmptyTracerImpl>>
    void format_dump(Formatter& out, Tracer tracer = Tracer()) const;
};

#endif //TRANSCRIPTION_H
