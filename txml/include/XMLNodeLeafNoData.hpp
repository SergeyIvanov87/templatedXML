#ifndef XML_NODE_LEAF_NO_DATA_HPP
#define XML_NODE_LEAF_NO_DATA_HPP

#include <txml/include/fwd/XMLNodeLeafNoData.h>
#include <txml/include/utils.h>

#include <txml/include/engine/TextReaderWrap.hpp>
#include <txml/include/engine/TracerHelper.hpp>

namespace txml
{
#define TEMPL_ARGS_DECL    class Impl
#define TEMPL_ARGS_DEF     Impl


template<TEMPL_ARGS_DECL>
template<class Tracer>
std::optional<Impl> XMLNodeLeafNoData<TEMPL_ARGS_DEF>::create(TextReaderWrapper &reader, Tracer tracer)
{
    const std::string &name = reader.get_name();
    if (name != Impl::class_name())
    {
        throw std::runtime_error(std::string("Expected: ") + std::string(Impl::class_name()) +
                                 ", got: " + name);
    }

    std::optional<Impl> ret;
    TextReaderWrapper::NodeType nodeType = reader.get_node_type();
    if (nodeType != Impl::class_node_type())
    {
        tracer.trace("<skip '", Impl::class_name(), "' for node type: ", to_string(nodeType),
                     ", expected node type: ", to_string(TextReaderWrapper::NodeType::Text));
        return ret;
    }


    tracer.trace("Open tag '", Impl::class_name(), "'");
    ret = Impl();//(std::string(it, tmp_value.end()))); = //Impl::create_impl(reader, tracer);
    tracer.trace("Close tag '", Impl::class_name(), "'");
    return ret;
}

template<TEMPL_ARGS_DECL>
template<class Tracer>
void XMLNodeLeafNoData<TEMPL_ARGS_DEF>::fill_impl(TextReaderWrapper &reader, Tracer tracer)
{
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLNodeLeafNoData<TEMPL_ARGS_DEF>::format_serialize_request(Formatter& out, Tracer tracer) const
{
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - PERFORM");
    out.template map<Impl>(*static_cast<const Impl *>(this), tracer);
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - ACK: ", static_cast<const Impl&>(*this));
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLNodeLeafNoData<TEMPL_ARGS_DEF>::schema_serialize_request(Formatter& out, Tracer tracer)
{
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - PERFORM");
    out.template map<Impl>(tracer);
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - ACK");
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
std::optional<Impl> XMLNodeLeafNoData<TEMPL_ARGS_DEF>::format_deserialize_request(Formatter& in, Tracer tracer)
{
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - PERFORM");
    auto ret = in.template map<Impl>(tracer);
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, ret ? " - ACK: " : " - NACK: ", ret);
    return ret;
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLNodeLeafNoData<TEMPL_ARGS_DEF>::format_redeserialize_request(Formatter& in, Tracer tracer)
{
}

#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif //XML_NODE_LEAF_NO_DATA_HPP
