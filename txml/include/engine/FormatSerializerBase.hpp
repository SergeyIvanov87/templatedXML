#ifndef FORMAT_SERIALIZER_HPP
#define FORMAT_SERIALIZER_HPP


#include <txml/include/engine/fwd/FormatSerializerBase.h>
#include <txml/include/details/SerializePolicies.hpp>

namespace txml
{
namespace details
{
template<class Impl, class ElementType>
struct SingleElementSerializerBase
{
    template<class Tracer>
    void invoke(const ElementType& val, Tracer tracer)
    {
        static_cast<Impl*>(this)->serialize_impl(val, tracer);
    }

protected:
    ~SingleElementSerializerBase() = default;
};
} // namespace details

#define TEMPL_ARGS_DECL    class Impl, class UnscopedElementProcessingPolicyT, class ...ElementType
#define TEMPL_ARGS_DEF     Impl, UnscopedElementProcessingPolicyT, ElementType...

template<TEMPL_ARGS_DECL>
template<class InElement, class Tracer>
void FormatSerializerBase<TEMPL_ARGS_DEF>::map(const InElement& in_val, Tracer tracer)
{
    if constexpr(! std::disjunction_v<std::is_same<InElement,ElementType>...>)
    {
        UnscopedElementProcessingPolicyType::template process<SelfType, InElement, Tracer>(*this, in_val, tracer);
    }
    else
    {
        //details::SingleElementSerializerBase<Impl, InElement>::invoke(in_val, tracer);
        return static_cast<details::SingleElementSerializerBase<Impl, InElement>*>(this)->invoke(in_val, tracer);
    }
}

template<TEMPL_ARGS_DECL>
template <class InElement>
constexpr bool FormatSerializerBase<TEMPL_ARGS_DEF>::is_registered_element()
{
    return std::disjunction_v<std::is_same<InElement, ElementType>...>;
}


#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif // FORMAT_SERIALIZER_HPP
