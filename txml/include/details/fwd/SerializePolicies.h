#ifndef SERIALIZE_POLICIES_H
#define SERIALIZE_POLICIES_H

#include <type_traits>

namespace txml
{
struct SkipUnscopedElement
{
    template <class Serializer, class UnscopedElementType, class Tracer>
    static void process(Serializer &instance, const UnscopedElementType&, Tracer tracer);

    template <class Serializer, class UnscopedElementType, class Tracer>
    static void process(Serializer &instance, Tracer tracer);
};


struct StaticCheckUnscopedElement
{
    template <class Serializer, class UnscopedElementType, class Tracer>
    static void process(Serializer &instance, const UnscopedElementType&, Tracer tracer);

    template <class Serializer, class UnscopedElementType, class Tracer>
    static void process(Serializer &instance, Tracer tracer);
private:

    template<class One, class ...Other>
    static constexpr bool is_one_of(const std::tuple<Other...>* )
    {
        return std::disjunction_v<std::is_same<One,Other>...>;
    }
};
} // namespace txml
#endif // SERIALIZE_POLICIES_H
