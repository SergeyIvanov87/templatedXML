#ifndef FORMAT_DESERIALIZER_H
#define FORMAT_DESERIALIZER_H

#include <tuple>
#include <txml/include/details/fwd/SerializePolicies.h>
#include <txml/include/engine/fwd/TagHolder.h>

namespace txml
{
namespace details
{
template<class Impl, class ElementType>
struct SingleElementDeserializerBase;

template<class T>
struct SchemaDTag : public T::tags_t {
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
    std::shared_ptr<InElement> map(Tracer tracer);

protected:
    ~FormatDeserializerBase() = default;

};
} // namespace txml
#endif //FORMAT_DESERIALIZER_H
