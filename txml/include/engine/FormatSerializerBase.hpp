#ifndef FORMAT_SERIALIZER_H
#define FORMAT_SERIALIZER_H

#include <tuple>
#include <type_traits>

#include <txml/include/details/SerializePolicies.hpp>

namespace txml
{
namespace details
{
template<class Impl, class ElementType>
struct SingleElementSerializerBase;
} // namespace details


template<class Impl, class UnscopedElementProcessingPolicyT, class ...ElementType>
struct FormatSerializerBase : public details::SingleElementSerializerBase<Impl, ElementType>...
{
    using ImplType = Impl;
    using UnscopedElementProcessingPolicyType = UnscopedElementProcessingPolicyT;
    using ElementTupleType = std::tuple<ElementType...>;
    using SelfType = FormatSerializerBase<Impl, UnscopedElementProcessingPolicyType, ElementType...>;

    template<class InElement, class Tracer>
    void map(const InElement& in_val, Tracer tracer)
    {
        if constexpr(! std::disjunction_v<std::is_same<InElement,ElementType>...>)
        {
            UnscopedElementProcessingPolicyType::template process<SelfType, InElement, Tracer>(*this, in_val, tracer);
        }
        else
        {
            details::SingleElementSerializerBase<Impl, InElement>::invoke(in_val, tracer);
        }
    }

protected:
    ~FormatSerializerBase() = default;

};


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
} // namespace txml
#endif //FORMAT_SERIALIZER_H
