#ifndef SERIALIZE_POLICIES_HPP
#define SERIALIZE_POLICIES_HPP

namespace txml
{
struct SkipUnscopedElement
{
    template <class Serializer, class UnscopedElementType, class Tracer>
    static void process(Serializer &instance, const UnscopedElementType& in_val, Tracer tracer)
    {
        tracer.trace(__PRETTY_FUNCTION__, "\nskip serialize for: ", UnscopedElementType::class_name());
    }
};


struct StaticCheckUnscopedElement
{
    template <class Serializer, class UnscopedElementType, class Tracer>
    static void process(Serializer &instance, const UnscopedElementType& in_val, Tracer tracer)
    {
        static_assert(is_one_of<UnscopedElementType>(static_cast<typename Serializer::ElementTupleType*>(nullptr)), "Unexpected Element type for serialize");
    }
private:

    template<class One, class ...Other>
    static constexpr bool is_one_of(const std::tuple<Other...>* )
    {
        return std::disjunction_v<std::is_same<One,Other>...>;
    }
};
} // namespace txml
#endif //SERIALIZE_POLICIES_HPP
