#ifndef XDXF_VALUEBASE_HPP
#define XDXF_VALUEBASE_HPP

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
template<class Value, class Tracer/* = txml::EmptyTracer>*/>
std::shared_ptr<Value> XMLNode<TEMPL_ARGS_DEF>::create(std::string &name, TextReaderWrapper &reader, Tracer tracer)
{
    return Value::create(name, reader);
}

template<TEMPL_ARGS_DECL>
template<class Tracer>
bool XMLNode<TEMPL_ARGS_DEF>::initialize(std::string &name, TextReaderWrapper &reader, Tracer tracer/* = Tracer()*/)
{
    tracer.trace(__FUNCTION__, " '", Impl::class_name(), "' - got: '", name, "'");
    this->template create_from<XMLCreator>(name, reader, tracer);
    return true;
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
    tracer.trace(__FUNCTION__, " - ", Impl::class_name());
    out.map(static_cast<const Impl&>(*this), tracer);
}


template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::format_deserialize_impl(Formatter& in, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", Impl::class_name());
    in.template map<Impl>(tracer);
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", Impl::class_name());
    out.template map<Impl>(tracer);
}

template<TEMPL_ARGS_DECL>
inline std::shared_ptr<XMLNode<TEMPL_ARGS_DEF>> XMLNode<TEMPL_ARGS_DEF>::get_ptr()
{
    return this->shared_from_this();
}
#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif //XDXF_VALUEBASE_HPP
