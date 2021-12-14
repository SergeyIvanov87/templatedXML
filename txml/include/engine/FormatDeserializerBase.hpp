#ifndef FORMAT_DESERIALIZER_HPP
#define FORMAT_DESERIALIZER_HPP

#include <txml/include/engine/fwd/FormatDeserializerBase.h>
#include <txml/include/details/SerializePolicies.hpp>

namespace txml
{
namespace details
{
template<class Impl, class ElementType>
struct SingleElementDeserializerBase
{
    template<class Tracer>
    std::shared_ptr<ElementType> invoke(Tracer tracer)
    {
        return static_cast<Impl*>(this)->deserialize_impl(SchemaDTag<ElementType> {} , tracer);
    }

protected:
    ~SingleElementDeserializerBase() = default;
};
} // namespace details


#define TEMPL_ARGS_DECL    class Impl, class UnscopedElementProcessingPolicyT, class ...ElementType
#define TEMPL_ARGS_DEF     Impl, UnscopedElementProcessingPolicyT, ElementType...

template<TEMPL_ARGS_DECL>
template<class InElement, class Tracer>
std::shared_ptr<InElement> FormatDeserializerBase<TEMPL_ARGS_DEF>::map(Tracer tracer)
{
    if constexpr(! std::disjunction_v<std::is_same<InElement,ElementType>...>)
    {
        UnscopedElementProcessingPolicyType::template process<SelfType, InElement, Tracer>(*this, tracer);
    }
    else
    {
        //return details::SingleElementDeserializerBase<Impl, InElement>::invoke(tracer);
        return static_cast<details::SingleElementDeserializerBase<Impl, InElement>*>(this)->invoke(tracer);
    }
    return {};
}

template<TEMPL_ARGS_DECL>
template <class InElement>
constexpr bool FormatDeserializerBase<TEMPL_ARGS_DEF>::is_registered_element()
{
    return std::disjunction_v<std::is_same<InElement, ElementType>...>;
}

#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif // FORMAT_DESERIALIZER_HPP
