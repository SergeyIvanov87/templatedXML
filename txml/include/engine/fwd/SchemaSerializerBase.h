#ifndef SCHEMA_SERIALIZER_H
#define SCHEMA_SERIALIZER_H

#include <tuple>
#include <txml/include/details/fwd/SerializePolicies.h>
#include <txml/include/engine/fwd/TagHolder.h>

namespace txml
{
namespace details
{
template<class Impl, class ElementType>
struct SingleElementSchemaSerializerBase;

template<class T>
struct SchemaTag : public T::tags_t  {
    using Type = T;
};
} // namespace details


template<class Impl, class UnscopedElementProcessingPolicyT, class ...ElementType>
struct SchemaSerializerBase : public details::SingleElementSchemaSerializerBase<Impl, ElementType>...
{
    using ImplType = Impl;
    using UnscopedElementProcessingPolicyType = UnscopedElementProcessingPolicyT;
    using ElementTupleType = std::tuple<ElementType...>;
    using SelfType = SchemaSerializerBase<Impl, UnscopedElementProcessingPolicyType, ElementType...>;

    template<class InElement, class Tracer>
    void map(Tracer tracer);
protected:
    ~SchemaSerializerBase() = default;

};
} // namespace txml
#endif //SCHEMA_SERIALIZER_H
