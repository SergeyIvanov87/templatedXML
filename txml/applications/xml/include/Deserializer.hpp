#ifndef TXML_APPLICATION_XML_DESERIALIZER_HPP
#define TXML_APPLICATION_XML_DESERIALIZER_HPP

#include <txml/include/engine/FormatDeserializerBase.hpp>
#include <txml/applications/xml/include/fwd/Deserializer.h>

namespace xml
{
#define TEMPL_ARGS_DECL    class Impl, class ...DeserializedItems
#define TEMPL_ARGS_DEF     Impl, DeserializedItems...

template<TEMPL_ARGS_DECL>
FromXML<TEMPL_ARGS_DEF>::FromXML(txml::TextReaderWrapper &stream) :
  in(stream)
{
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::shared_ptr<DeserializedItem> FromXML<TEMPL_ARGS_DEF>::deserialize_impl(txml::details::SchemaDTag<DeserializedItem>, Tracer tracer)
{
    return deserialize_tag_impl<DeserializedItem>(txml::details::SchemaDTag<DeserializedItem> {}, tracer);
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::shared_ptr<DeserializedItem> FromXML<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::ArrayTag&, Tracer &tracer)
{
    if (!check_node_param<DeserializedItem> (in, tracer)) {
        return {};
    }

    return create_deserialized_node<DeserializedItem>(tracer);
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::shared_ptr<DeserializedItem> FromXML<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::ContainerTag&, Tracer &tracer)
{
    if (!check_node_param<DeserializedItem> (in, tracer)) {
        return {};
    }

    return create_deserialized_node<DeserializedItem>(tracer);
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::shared_ptr<DeserializedItem> FromXML<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::LeafTag&, Tracer &tracer)
{
    if (!check_node_param<DeserializedItem> (in, tracer)) {
        return {};
    }

    return DeserializedItem::create_impl(in, tracer);
}


template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::shared_ptr<DeserializedItem> FromXML<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::NoDataTag&, Tracer &tracer)
{
    if (!check_node_param<DeserializedItem> (in, tracer)) {
        return {};
    }

    return std::make_shared<DeserializedItem>();
}


template<TEMPL_ARGS_DECL>
template<class NodeType, class Tracer>
bool FromXML<TEMPL_ARGS_DEF>::check_node_param(const txml::TextReaderWrapper &reader, Tracer tracer)
{
    const std::string &name = reader.get_name();
    txml::TextReaderWrapper::NodeType nodeType = reader.get_node_type();
    auto depth = reader.get_depth();
    tracer.trace("Found '", to_string(nodeType), "', tag name: '", name,
                 "', depth: ", depth);
    if (name != NodeType::class_name() || nodeType != NodeType::class_node_type())
    {
        tracer.trace("Expected '", to_string(NodeType::class_node_type()), "', tag name: '", NodeType::class_name(), "'");
        return false;
    }
    return true;
}

template<TEMPL_ARGS_DECL>
template<class NodeType, class Tracer>
std::shared_ptr<NodeType> FromXML<TEMPL_ARGS_DEF>::create_deserialized_node(Tracer tracer)
{
    int node_depth = in.get_depth();

    std::shared_ptr<NodeType> ret = std::make_shared<NodeType>();
    tracer.trace("Create node '", NodeType::class_name(), "' handle: ",
                 ret.get(),
                 ", depth: ", node_depth);

    bool get_next = false;
    Tracer node_tracer = tracer;
    while (in.read())
    {
        node_tracer.trace("Open node '", to_string(in.get_node_type()),
                          "', tag name: '", in.get_name(),
                          "', depth: ", in.get_depth());
        if (in.get_name() == NodeType::class_name() &&
            in.get_node_type() == txml::TextReaderWrapper::NodeType::EndElement &&
            node_depth == in.get_depth())
        {
            tracer.trace("Close node '", to_string(NodeType::class_node_type()),
                         "', tag name: '",  NodeType::class_name(),
                         "' handle: ", ret.get(),
                         "', depth: ", node_depth);
            in.read();
            break;
        }
        bool node_processed = ret->format_deserialize_elements(*this, tracer);
        get_next |= node_processed;
        if (!node_processed && in.get_node_type() == txml::TextReaderWrapper::NodeType::Element)
        {
            const std::string& unprocessed_name = in.get_name();
            int depth = in.get_depth();
            node_tracer.trace("Skipping node: ", unprocessed_name, ", type: ",
                              to_string(in.get_node_type()), ", depth: ", depth);
            Tracer sub_tracer = node_tracer;
            while (in.read())
            {
                if ((in.get_name() == unprocessed_name &&
                     in.get_node_type() == txml::TextReaderWrapper::NodeType::EndElement &&
                     in.get_depth() == depth)

                     ||

                    in.get_depth() <= depth
                   )
                {
                    break;
                }
                else
                {
                    sub_tracer.trace("To skip node: ", in.get_name(), ", type: ",
                                     to_string(in.get_node_type()), ", depth: ", in.get_depth());
                }
            }
            node_tracer.trace("Skipped node: ", unprocessed_name, ", depth: ", depth);
        }
    }
    tracer.trace("Return node '", NodeType::class_name(), "' handle: ", ret.get());
    return ret;
}
#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace xml
#endif // TXML_APPLICATION_XML_DESERIALIZER_HPP
