#ifndef XML_ARRAY_HPP
#define XML_ARRAY_HPP

#include <txml/include/fwd/XMLArray.h>
#include <txml/include/details/GenericContainerImpl.hpp>

#include <txml/include/XMLProducible.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>
#include <txml/include/engine/TextReaderWrap.hpp>
#include <txml/include/engine/TracerHelper.hpp>

namespace txml
{
#define TEMPL_ARGS_DECL    class Impl, class ElementType
#define TEMPL_ARGS_DEF     Impl, ElementType

template<TEMPL_ARGS_DECL>
template<class Tracer>
bool XMLArray<TEMPL_ARGS_DEF>::initialize(TextReaderWrapper &reader, Tracer tracer/* = Tracer()*/)
{
    const std::string &name = reader.get_name();
    tracer.trace("try saturate array '", Impl::class_name(), "' by '", name, "'");
    size_t ret = this->template create_from<XMLCreator>(reader, tracer);
    tracer.trace("saturation array '", Impl::class_name(), "' with: '", name, "', got count: ", ret);
    return ret;
}


template<TEMPL_ARGS_DECL>
void XMLArray<TEMPL_ARGS_DEF>::serialize_impl(std::ostream &out) const
{
    Container::serialize_elements(out);
}

template<TEMPL_ARGS_DECL>
template<class Tracer>
void XMLArray<TEMPL_ARGS_DEF>::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Impl::class_name() << ">";
    Container::serialize_elements(out, tracer, txml::no_sep);
    out << "</" << Impl::class_name() << ">\n";
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLArray<TEMPL_ARGS_DEF>::format_serialize_request(Formatter& out, Tracer tracer) const
{
    tracer.trace("map array node '", Impl::class_name(), "'");
    out.map(static_cast<const Impl&>(*this), tracer);
    tracer.trace("unmap array node '", Impl::class_name(), "'");
}


template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
std::optional<Impl> XMLArray<TEMPL_ARGS_DEF>::format_deserialize_request(Formatter& in, Tracer tracer)
{
    tracer.trace("Begin deserialize map '", Impl::class_name(), "'");
    auto ret = in.template map<Impl>(tracer);
    tracer.trace("End deserialize map '", Impl::class_name(), "', handle: ", ret);
    return ret;
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLArray<TEMPL_ARGS_DEF>::format_redeserialize_request(Formatter& in, Tracer tracer)
{
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLArray<TEMPL_ARGS_DEF>::schema_serialize_request(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", Impl::class_name());
    out.template map<Impl>(tracer);
}

#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif //XML_ARRAY_HPP
