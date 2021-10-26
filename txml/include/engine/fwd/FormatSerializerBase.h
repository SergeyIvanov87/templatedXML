#ifndef FORMAT_SERIALIZER_H
#define FORMAT_SERIALIZER_H

#include <tuple>
#include <txml/include/details/fwd/SerializePolicies.h>

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
    void map(const InElement& in_val, Tracer tracer);

protected:
    ~FormatSerializerBase() = default;

};
} // namespace txml
#endif //FORMAT_SERIALIZER_H
