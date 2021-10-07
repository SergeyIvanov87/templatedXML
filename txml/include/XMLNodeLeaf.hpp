#ifndef XDXF_TYPED_VALUE_HPP
#define XDXF_TYPED_VALUE_HPP

#include <txml/include/fwd/XMLNodeLeaf.h>
#include <txml/include/utils.h>

#include <txml/include/engine/TextReaderWrap.hpp>

namespace txml
{
#define TEMPL_ARGS_DECL    class Impl, class T
#define TEMPL_ARGS_DEF     Impl, T

template<TEMPL_ARGS_DECL>
XMLNodeLeaf<TEMPL_ARGS_DEF>::XMLNodeLeaf(value_t&& v) :
    base(),
    val(std::move(v))
{
}

template<TEMPL_ARGS_DECL>
const typename XMLNodeLeaf<TEMPL_ARGS_DEF>::value_t &XMLNodeLeaf<TEMPL_ARGS_DEF>::getValue() const
{
    return val;
}

template<TEMPL_ARGS_DECL>
typename XMLNodeLeaf<TEMPL_ARGS_DEF>::value_t& XMLNodeLeaf<TEMPL_ARGS_DEF>::getValue()
{
    return val;
}

template<TEMPL_ARGS_DECL>
template<class Tracer>
std::shared_ptr<Impl> XMLNodeLeaf<TEMPL_ARGS_DEF>::create(TextReaderWrapper &reader, Tracer tracer)
{
    const std::string &name = reader.get_name();
    if (name != Impl::class_name())
    {
        throw std::runtime_error(std::string("Expected: ") + Impl::class_name() +
                                 ", got: " + name);
    }

    std::shared_ptr<Impl> ret;
    TextReaderWrapper::NodeType nodeType = reader.get_node_type();
    if (nodeType != Impl::class_node_type())
    {
        tracer.trace("<skip '", Impl::class_name(), "' for node type: ", to_string(nodeType),
                     ", expected node type: ", to_string(TextReaderWrapper::NodeType::Text));
        return ret;
    }


    tracer.trace("Open tag '", Impl::class_name(), "'");
    ret = Impl::create_impl(reader, tracer);
    tracer.trace("Close tag '", Impl::class_name(), "'");
    return ret;
}

template<TEMPL_ARGS_DECL>
template<class Tracer>
void XMLNodeLeaf<TEMPL_ARGS_DEF>::fill_impl(TextReaderWrapper &reader, Tracer tracer)
{
}
#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif //XDXF_TYPED_VALUE_HPP
