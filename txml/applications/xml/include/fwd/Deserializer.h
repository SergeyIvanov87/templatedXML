#ifndef TXML_APPLICATION_XML_FWD_DESERIALIZER_H
#define TXML_APPLICATION_XML_FWD_DESERIALIZER_H

#include <txml/include/engine/fwd/FormatDeserializerBase.h>
#include <txml/applications/xml/include/fwd/DeserializerCore.h>

namespace xml
{

template<class Impl, class ...DeserializedItems>
struct FromXML : public virtual DeserializerCore,
                 public txml::FormatDeserializerBase<Impl, txml::StaticCheckUnscopedElement,
                                                     DeserializedItems...>
{
    using core_t = DeserializerCore;
    using xml_core_t = core_t::xml_core_t;
    using in_stream_core_t = xml_core_t;
    using ctor_arg_t = core_t::ctor_arg_t;

    FromXML(in_stream_core_t &stream, ctor_arg_t = core_t::default_ctor_arg());

    // default deserialization routine
    template<class DeserializedItem, class Tracer>
    std::optional<DeserializedItem> deserialize_impl(txml::details::SchemaDTag<DeserializedItem>, Tracer tracer);

protected:

    template<class DeserializedItem, class Tracer>
    std::optional<DeserializedItem> deserialize_tag_impl(const txml::ArrayTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::optional<DeserializedItem> deserialize_tag_impl(const txml::ContainerTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::optional<DeserializedItem> deserialize_tag_impl(const txml::LeafTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::optional<DeserializedItem> deserialize_tag_impl(const txml::NoDataTag&, Tracer &tracer);

    template<class NodeType, class Tracer>
    bool check_node_param(const xml_core_t &reader, Tracer tracer);

    template<class NodeType, class Tracer>
    std::optional<NodeType> create_deserialized_node(Tracer tracer);
};
} // namespace xml
#endif // TXML_APPLICATION_XML_FWD_DESERIALIZER_H
