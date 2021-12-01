#ifndef SERIALIZER_DESERIALIZER_DISPATCHER_H
#define SERIALIZER_DESERIALIZER_DISPATCHER_H

#include <type_traits>

namespace txml
{
namespace details
{
struct EmptyContext {};
template <class InElement, class... Others>
struct ContextResolver {};

template <class InElement, class T, class... Ctx>
struct ContextResolver<InElement, T, Ctx...> {
    using type = typename std::conditional<T::template is_registered_element<InElement>(),
                                           T,
                                           typename ContextResolver<InElement, Ctx...>::type>::type;
};

template <class InElement, class T>
struct ContextResolver<InElement, T> {
    using type = typename std::conditional<T::template is_registered_element<InElement>(), T, EmptyContext>::type;
};
}
template <class ...Contexts>
struct Dispatcher : public Contexts...
{
    //using UnscopedElementProcessingPolicyType = UnscopedElementProcessingPolicyT;

    template<class ...Args>
    Dispatcher(Args &&...args) :
        Contexts{std::forward<Args>(args)...}...
    {
    }

    template<class InElement, class Tracer>
    void map(Tracer tracer) {
        auto* element_processing_context = this->dispatch_context<InElement>();
        if constexpr (not std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template map<InElement>(tracer);
        }
    }

    template<class InElement, class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<InElement>, Tracer tracer)
    {
        auto* element_processing_context = this->dispatch_context<InElement>();
        //element_processing_context->template serialize_schema_tag_impl<InElement>(typename InElement::tags_t {}, tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_schema_impl(txml::details::SchemaTag<InElement> {} , tracer);
        }
    }

    template<class InElement, class Tracer>
    void serialize_schema_tag_impl(const txml::ArrayTag&, Tracer &tracer)
    {
        auto* element_processing_context = this->dispatch_context<InElement>();
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_schema_tag_impl<InElement>(txml::ArrayTag{} , tracer);
        }
    }

    template<class InElement, class Tracer>
    void serialize_schema_tag_impl(const txml::ContainerTag&, Tracer &tracer)
    {
        auto* element_processing_context = this->dispatch_context<InElement>();
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_schema_tag_impl<InElement>(txml::ContainerTag{} , tracer);
        }
    }

    template<class InElement, class Tracer>
    void serialize_schema_tag_impl(const txml::LeafTag&, Tracer &tracer)
    {
        auto* element_processing_context = this->dispatch_context<InElement>();
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_schema_tag_impl<InElement>(txml::LeafTag{} , tracer);
        }
    }


    template <class InElement>
    typename std::add_pointer<typename details::ContextResolver<InElement, Contexts...>::type>::type
    dispatch_context() {
        using ResolvedContextType = typename details::ContextResolver<InElement, Contexts...>::type;

        /* TODO adapt unscoped element policy or introduce new */
        if constexpr(not std::is_same<ResolvedContextType, details::EmptyContext>::value)
        {
            return static_cast<typename std::add_pointer<ResolvedContextType>::type>(this);
        }
        else
        {
            /* static_assert(not std::is_same<ResolvedContextType, details::EmptyContext>::value,
                      "Not found appropriate context type which holds `InElement` for processing");*/
            return static_cast<details::EmptyContext*>(nullptr);
        }
    }
};
} // namespace txml
#endif // SERIALIZER_DESERIALIZER_DISPATCHER_H
