#ifndef TRANSCRIPTION_H
#define TRANSCRIPTION_H

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/fwd/XMLSerializable.h>

namespace xdxf
{
class TextElement;
class Transcription : public txml::XMLNode<Transcription, TextElement>,
                      public txml::XMLSerializable<Transcription>,
                      public txml::XMLFormatSerializable<Transcription>
{
public:
    using base = txml::XMLNode<Transcription, TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "tr";
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
};
} // namespace xdxf
#endif //TRANSCRIPTION_H
