#ifndef XDXF_VALUEBASE_HPP
#define XDXF_VALUEBASE_HPP

#include <txml/include/fwd/XMLNode.h>

#include <txml/include/XMLProducible.hpp>
#include <txml/include/XMLCreator.hpp>
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
inline std::shared_ptr<XMLNode<TEMPL_ARGS_DEF>> XMLNode<TEMPL_ARGS_DEF>::get_ptr()
{
    return this->shared_from_this();
}
#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif //XDXF_VALUEBASE_HPP