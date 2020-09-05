#ifndef XDXF_VALUEBASE_HPP
#define XDXF_VALUEBASE_HPP

#include "XMLNode.h"
#include "details/GenericCommandArguments.hpp"

#define TEMPL_ARGS_DECL    class ...ContainedValues
#define TEMPL_ARGS_DEF     ContainedValues...

template<TEMPL_ARGS_DECL>
template<class Value, class Tracer/* = EmptyTracer>*/>
std::shared_ptr<Value> XMLNode<TEMPL_ARGS_DEF>::create(std::string &name, xmlpp::TextReader &reader, Tracer tracer)
{
    return Value::create(name, reader);
}

template<TEMPL_ARGS_DECL>
void XMLNode<TEMPL_ARGS_DEF>::dump(std::ostream &out) const
{
    Container::dump_all(out);
}

template<TEMPL_ARGS_DECL>
inline std::shared_ptr<XMLNode<TEMPL_ARGS_DEF>> XMLNode<TEMPL_ARGS_DEF>::get_ptr()
{
    return this->shared_from_this();
}

#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
#endif //XDXF_VALUEBASE_HPP
