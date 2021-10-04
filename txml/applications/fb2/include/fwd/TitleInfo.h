#ifndef FB2_TITLE_INFO_H
#define FB2_TITLE_INFO_H

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

namespace fb2
{
class BookTitle;
class TitleInfo : public txml::XMLNode<TitleInfo, BookTitle>,
                  public txml::XMLSerializable<TitleInfo>,
                  public txml::XMLFormatDeserializable<TitleInfo>,
                  public txml::XMLSchemaSerializable<TitleInfo>
{
public:
    using base = txml::XMLNode<TitleInfo, BookTitle>;

    static constexpr const char *class_name()
    {
        return "title-info";
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
#endif //FB2_TITLE_INFO_H
