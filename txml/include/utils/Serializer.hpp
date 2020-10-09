#ifndef FORMAT_SERIALIZER_H
#define FORMAT_SERIALIZER_H

#include <tuple>
#include <type_traits>

#include "../details/SerializePolicies.hpp"

template<class Impl, class UnscopedPolicy, class ...ElementType>
struct FormatSerializerBase // TODO interface
{
    using ImplType = Impl;
    using UnscopedPolicyType = UnscopedPolicy;
    using ElementTupleType = std::tuple<ElementType...>;
    using SelfType = FormatSerializerBase<Impl, UnscopedPolicyType, ElementType...>;

    template<class InElement, class Tracer>
    void map(const InElement& in_val, Tracer tracer)
    {
        if constexpr(! std::disjunction_v<std::is_same<InElement,ElementType>...>)
        {
            UnscopedPolicyType::template process<SelfType, InElement, Tracer>(*this, in_val, tracer);
        }
        else
        {
            static_cast<ImplType*>(this)->template map_impl(in_val, tracer);
        }
    }
};

#endif //FORMAT_SERIALIZER_H
