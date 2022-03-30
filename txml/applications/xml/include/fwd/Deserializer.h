#ifndef TXML_APPLICATION_XML_FWD_DESERIALIZER_H
#define TXML_APPLICATION_XML_FWD_DESERIALIZER_H

#include <txml/include/engine/fwd/FormatDeserializerBase.h>

#include <txml/include/engine/TextReaderWrap.hpp>

namespace xml
{

template<class Impl, class ...DeserializedItems>
struct FromXML : public txml::FormatDeserializerBase<Impl, txml::StaticCheckUnscopedElement,
                                                     DeserializedItems...>
{
    FromXML(txml::TextReaderWrapper &stream);

    // default deserialization routine
    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_impl(txml::details::SchemaDTag<DeserializedItem>, Tracer tracer);

protected:
    txml::TextReaderWrapper &in;

    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::ArrayTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::ContainerTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::LeafTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::NoDataTag&, Tracer &tracer);

    template<class NodeType, class Tracer>
    bool check_node_param(const txml::TextReaderWrapper &reader, Tracer tracer);

    template<class NodeType, class Tracer>
    std::shared_ptr<NodeType> create_deserialized_node(Tracer tracer);
};
} // namespace xml
#endif // TXML_APPLICATION_XML_FWD_DESERIALIZER_H
