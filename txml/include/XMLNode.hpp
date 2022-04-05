#ifndef XML_NODE_HPP
#define XML_NODE_HPP

#include <txml/include/fwd/XMLNode.h>

#include <txml/include/XMLProducible.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>
#include <txml/include/details/GenericCommandArguments.hpp>
#include <txml/include/engine/TextReaderWrap.hpp>

namespace txml
{
#define TEMPL_ARGS_DECL    class Impl, class ...ContainedValues
#define TEMPL_ARGS_DEF     Impl, ContainedValues...

template<TEMPL_ARGS_DECL>
template<class Tracer>
bool XMLNode<TEMPL_ARGS_DEF>::initialize(TextReaderWrapper &reader, Tracer tracer/* = Tracer()*/)
{
    const std::string &name = reader.get_name();
    tracer.trace("try saturate node '", Impl::class_name(), "' with: '", name,
                 "', expected count: ", sizeof...(ContainedValues));
    size_t ret = this->template create_from<XMLCreator>(reader, tracer);
    tracer.trace("saturation node '", Impl::class_name(), "' with: '", name,
                "', ratio got: ", ret, "/", sizeof...(ContainedValues));
    return ret;
}


template<TEMPL_ARGS_DECL>
void XMLNode<TEMPL_ARGS_DEF>::serialize_impl(std::ostream &out) const
{
    Container::serialize_elements(out);
}

template<TEMPL_ARGS_DECL>
template<class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Impl::class_name() << ">";
    Container::serialize_elements(out, tracer, txml::no_sep);
    out << "</" << Impl::class_name() << ">\n";
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::format_serialize_impl(Formatter& out, Tracer tracer) const
{
    tracer.trace("map node '", Impl::class_name(), "'");
    out.map(static_cast<const Impl&>(*this), tracer);
    tracer.trace("unmap node '", Impl::class_name(), "'");
}


template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
std::shared_ptr<Impl> XMLNode<TEMPL_ARGS_DEF>::format_deserialize_impl(Formatter& in, Tracer tracer)
{
    tracer.trace("Begin deserialize map '", Impl::class_name(), "'");
    auto ret = in.template map<Impl>(tracer);
    tracer.trace("End deserialize map '", Impl::class_name(), "', handle: ", ret.get());
    return ret;
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::format_redeserialize_impl(Formatter& in, Tracer tracer)
{
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", Impl::class_name());
    out.template map<Impl>(tracer);
}
#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif //XML_NODE_HPP
