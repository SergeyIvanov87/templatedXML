#ifndef SCHEMA_SERIALIZER_H
#define SCHEMA_SERIALIZER_H

#include <tuple>
#include <type_traits>

#include <txml/include/details/SerializePolicies.hpp>

namespace txml
{
namespace details
{
template<class Impl, class ElementType>
struct SingleElementSchemaSerializerBase;
} // namespace details


template<class Impl, class UnscopedElementProcessingPolicyT, class ...ElementType>
struct SchemaSerializerBase : public details::SingleElementSchemaSerializerBase<Impl, ElementType>...
{
    using ImplType = Impl;
    using UnscopedElementProcessingPolicyType = UnscopedElementProcessingPolicyT;
    using ElementTupleType = std::tuple<ElementType...>;
    using SelfType = SchemaSerializerBase<Impl, UnscopedElementProcessingPolicyType, ElementType...>;

    template<class InElement, class Tracer>
    void map(Tracer tracer)
    {
        if constexpr(! std::disjunction_v<std::is_same<InElement,ElementType>...>)
        {
            UnscopedElementProcessingPolicyType::template process<SelfType, InElement, Tracer>(*this, tracer);
        }
        else
        {
            details::SingleElementSchemaSerializerBase<Impl, InElement>::invoke(tracer);
        }
    }

protected:
    ~SchemaSerializerBase() = default;

};


namespace details
{
template<class Impl, class ElementType>
struct SingleElementSchemaSerializerBase
{
    template<class Tracer>
    void invoke(Tracer tracer)
    {
        static_cast<Impl*>(this)->serialize_impl(static_cast<const ElementType*>(nullptr) , tracer);
    }

protected:
    ~SingleElementSchemaSerializerBase() = default;
};
} // namespace details
} // namespace txml
#endif //SCHEMA_SERIALIZER_H
