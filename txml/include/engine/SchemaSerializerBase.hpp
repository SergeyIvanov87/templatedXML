#ifndef SCHEMA_SERIALIZER_HPP
#define SCHEMA_SERIALIZER_HPP

#include <tuple>
#include <type_traits>

#include <txml/include/details/SerializePolicies.hpp>
#include <txml/include/engine/fwd/SchemaSerializerBase.h>

namespace txml
{
namespace details
{
template<class Impl, class ElementType>
struct SingleElementSchemaSerializerBase
{
    template<class Tracer>
    void invoke(Tracer tracer)
    {
        static_cast<Impl*>(this)->serialize_schema_impl(SchemaTag<ElementType> {} , tracer);
    }

protected:
    ~SingleElementSchemaSerializerBase() = default;
};
} // namespace details

#define TEMPL_ARGS_DECL    class Impl, class UnscopedElementProcessingPolicyT, class ...ElementType
#define TEMPL_ARGS_DEF     Impl, UnscopedElementProcessingPolicyT, ElementType...

template<TEMPL_ARGS_DECL>
template<class InElement, class Tracer>
void SchemaSerializerBase<TEMPL_ARGS_DEF>::map(Tracer tracer)
{
    /*if constexpr(! std::disjunction_v<std::is_same<InElement,ElementType>...>)
    {
        UnscopedElementProcessingPolicyType::template process<SelfType, InElement, Tracer>(*this, tracer);
    }
    else*/
    //{
        static_cast<details::SingleElementSchemaSerializerBase<Impl, InElement>*>(this)->invoke(tracer);
    //}
}


template<TEMPL_ARGS_DECL>
template <class InElement>
constexpr bool SchemaSerializerBase<TEMPL_ARGS_DEF>::is_registered_element()
{
    return std::disjunction_v<std::is_same<InElement, ElementType>...>;
}

#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif // SCHEMA_SERIALIZER_HPP
