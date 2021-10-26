#ifndef SERIALIZE_POLICIES_HPP
#define SERIALIZE_POLICIES_HPP

#include <txml/include/details/fwd/SerializePolicies.h>

namespace txml
{

#define TEMPL_ARGS_DECL    class Impl, class UnscopedElementType, class Tracer
#define TEMPL_ARGS_DEF     Impl, UnscopedElementType, Tracer

template<TEMPL_ARGS_DECL>
void SkipUnscopedElement::process(Impl &, const UnscopedElementType&, Tracer tracer)
{
    tracer.trace(__PRETTY_FUNCTION__, "\nskip serialize/deserialize for: ", UnscopedElementType::class_name());
}

template<TEMPL_ARGS_DECL>
void SkipUnscopedElement::process(Impl &, Tracer tracer)
{
    tracer.trace(__PRETTY_FUNCTION__, "\nskip serialize/deserialize for: ", UnscopedElementType::class_name());
}


template<TEMPL_ARGS_DECL>
void StaticCheckUnscopedElement::process(Impl &, const UnscopedElementType&, Tracer tracer)
{
    static_assert(is_one_of<UnscopedElementType>(static_cast<typename Impl::ElementTupleType*>(nullptr)),
                                                 "Unexpected Element type for serialize/deserialize");
}

template<TEMPL_ARGS_DECL>
void StaticCheckUnscopedElement::process(Impl &, Tracer tracer)
{
    static_assert(is_one_of<UnscopedElementType>(static_cast<typename Impl::ElementTupleType*>(nullptr)),
                                                "Unexpected Element type for serialize");
}

#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif //SERIALIZE_POLICIES_HPP
