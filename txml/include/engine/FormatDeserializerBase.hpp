#ifndef FORMAT_DESERIALIZER_H
#define FORMAT_DESERIALIZER_H

#include <tuple>
#include <type_traits>

#include <txml/include/details/SerializePolicies.hpp>

namespace txml
{
namespace details
{
template<class Impl, class ElementType>
struct SingleElementDeserializerBase;

template<class T>
struct SchemaDTag {
    using Type = T;
};

} // namespace details


template<class Impl, class UnscopedElementProcessingPolicyT, class ...ElementType>
struct FormatDeserializerBase : public details::SingleElementDeserializerBase<Impl, ElementType>...
{
    using ImplType = Impl;
    using UnscopedElementProcessingPolicyType = UnscopedElementProcessingPolicyT;
    using ElementTupleType = std::tuple<ElementType...>;
    using SelfType = FormatDeserializerBase<Impl, UnscopedElementProcessingPolicyType, ElementType...>;

    template<class InElement, class Tracer>
    std::shared_ptr<InElement> map(Tracer tracer)
    {
        if constexpr(! std::disjunction_v<std::is_same<InElement,ElementType>...>)
        {
            UnscopedElementProcessingPolicyType::template process<SelfType, InElement, Tracer>(*this, tracer);
        }
        else
        {
            return details::SingleElementDeserializerBase<Impl, InElement>::invoke(tracer);
        }
        return {};
    }

protected:
    ~FormatDeserializerBase() = default;

};


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
} // namespace txml
#endif //FORMAT_DESERIALIZER_H
