#ifndef XDXF_TYPED_VALUE_HPP
#define XDXF_TYPED_VALUE_HPP
#include "XMLNodeLeaf.h"
#include "utils.h"

#define TEMPL_ARGS_DECL    class T
#define TEMPL_ARGS_DEF     T

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
void XMLNodeLeaf<TEMPL_ARGS_DEF>::fill_impl(std::string &name, xmlpp::TextReader &reader, Tracer tracer)
{
}
#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
#endif //XDXF_TYPED_VALUE_HPP
