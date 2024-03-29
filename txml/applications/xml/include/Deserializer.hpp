#ifndef TXML_APPLICATION_XML_DESERIALIZER_HPP
#define TXML_APPLICATION_XML_DESERIALIZER_HPP

#include <txml/include/engine/FormatDeserializerBase.hpp>
#include <txml/applications/json/include/DeserializerCore.hpp>
#include <txml/applications/xml/include/fwd/Deserializer.h>

namespace xml
{
#define TEMPL_ARGS_DECL    class Impl, class ...DeserializedItems
#define TEMPL_ARGS_DEF     Impl, DeserializedItems...

template<TEMPL_ARGS_DECL>
FromXML<TEMPL_ARGS_DEF>::FromXML(xml_core_t &stream, ctor_arg_t helper) :
  core_t(stream, helper)
{
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::optional<DeserializedItem> FromXML<TEMPL_ARGS_DEF>::deserialize_impl(txml::details::SchemaDTag<DeserializedItem>, Tracer tracer)
{
    return deserialize_tag_impl<DeserializedItem>(txml::details::SchemaDTag<DeserializedItem> {}, tracer);
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::optional<DeserializedItem> FromXML<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::ArrayTag&, Tracer &tracer)
{
    if (!check_node_param<DeserializedItem> (in, tracer)) {
        return {};
    }

    return create_deserialized_node<DeserializedItem>(tracer);
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::optional<DeserializedItem> FromXML<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::ContainerTag&, Tracer &tracer)
{
    if (!check_node_param<DeserializedItem> (in, tracer)) {
        return {};
    }

    return create_deserialized_node<DeserializedItem>(tracer);
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::optional<DeserializedItem> FromXML<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::LeafTag&, Tracer &tracer)
{
    if (!check_node_param<DeserializedItem> (in, tracer)) {
        return {};
    }

    return DeserializedItem::create_impl(in, tracer);
}


template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::optional<DeserializedItem> FromXML<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::NoDataTag&, Tracer &tracer)
{
    if (!check_node_param<DeserializedItem> (in, tracer)) {
        return {};
    }

    return std::make_optional<DeserializedItem>();
}


template<TEMPL_ARGS_DECL>
template<class NodeType, class Tracer>
bool FromXML<TEMPL_ARGS_DEF>::check_node_param(const xml_core_t &reader, Tracer tracer)
{
    const std::string &name = reader.get_name();
    txml::TextReaderWrapper::NodeType nodeType = reader.get_node_type();
    auto depth = reader.get_depth();

    tracer.trace(class_name(), " - AWAIT '", NodeType::class_name(), "' (", to_string(NodeType::class_node_type()), ")"
                 ", GOT '", name, "' (", to_string(nodeType), "), depth: ", depth);
    if (name != NodeType::class_name() || nodeType != NodeType::class_node_type())
    {
        return false;
    }
    return true;
}

template<TEMPL_ARGS_DECL>
template<class NodeType, class Tracer>
std::optional<NodeType> FromXML<TEMPL_ARGS_DEF>::create_deserialized_node(Tracer tracer)
{
    int node_depth = in.get_depth();

    std::optional<NodeType> ret = std::make_optional<NodeType>();
    tracer.trace(class_name(), " - Prepare EMPTY node '", NodeType::class_name(), "' ",
                 ret, ", depth: ", node_depth);

    bool get_next = false;
    Tracer node_tracer = tracer;
    while (in.read())
    {
        node_tracer.trace(class_name(), " - Opened node '", in.get_name(), "' (", to_string(in.get_node_type()),
                          "), depth: ", in.get_depth());
        // done when all subsequent elements deserialized and node closed
        if (in.get_name() == NodeType::class_name() &&
            in.get_node_type() == txml::TextReaderWrapper::NodeType::EndElement &&
            node_depth == in.get_depth())
        {
            tracer.trace(class_name(), " - Close opened node '", NodeType::class_name(), "' (", to_string(NodeType::class_node_type()),
                         ") ", ret,
                         ", depth: ", node_depth);
            in.read();
            break;
        }

        // start recursion
        bool node_processed = ret->make_format_deserialize(*this, tracer);
        get_next |= node_processed;

        // skip the same level elements which are not enumerated in DeserializedItems... list
        if (!node_processed && in.get_node_type() == txml::TextReaderWrapper::NodeType::Element)
        {
            const std::string& unprocessed_name = in.get_name();
            int depth = in.get_depth();
            node_tracer.trace(class_name(), " - Skipping opened node: '", unprocessed_name, "' (",
                              to_string(in.get_node_type()), "), depth: ", depth);
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
                    sub_tracer.trace(class_name(), " - To skip opened node: '", in.get_name(), "' (",
                                     to_string(in.get_node_type()), "), depth: ", in.get_depth());
                }
            }
            node_tracer.trace(class_name(), " - Skipped node: '", unprocessed_name, "', depth: ", depth);
        }

        // done when all subsequent elements deserialized and node closed
        if (in.get_name() == NodeType::class_name() &&
            in.get_node_type() == txml::TextReaderWrapper::NodeType::EndElement &&
            node_depth == in.get_depth())
        {
            tracer.trace(class_name(), " - Close opened node '", NodeType::class_name(), "' (", to_string(NodeType::class_node_type()),
                         ") ", ret,
                         ", depth: ", node_depth);
            in.read();
            break;
        }
    }
    tracer.trace(class_name(), " - Return node '", NodeType::class_name(), "' ", ret);
    return ret;
}
#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace xml
#endif // TXML_APPLICATION_XML_DESERIALIZER_HPP
