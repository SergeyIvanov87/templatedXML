#ifndef FB2_PUBLISH_INFO_H
#define FB2_PUBLISH_INFO_H

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

namespace fb2
{
class Empty;
class PublishInfo : public txml::XMLNode<PublishInfo, Empty>,
                    public txml::XMLSerializable<PublishInfo>,
                    public txml::XMLFormatDeserializable<PublishInfo>,
                    public txml::XMLSchemaSerializable<PublishInfo>
{
public:
    using base = txml::XMLNode<PublishInfo, Empty>;

    static constexpr const char *class_name()
    {
        return "publish-info";
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
#endif //FB2_PUBLISH_INFO_H
