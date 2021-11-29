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
    template<class ...Args>
    Dispatcher(Args &&...args) :
        Contexts{std::forward<Args>(args)...}...
    {
    }

    template<class InElement, class Tracer>
    void map(Tracer tracer) {
        auto* element_processing_context = this->dispatch_context<InElement>();
        element_processing_context->template map<InElement>(tracer);
    }


    template <class InElement>
    typename std::add_pointer<typename details::ContextResolver<InElement, Contexts...>::type>::type
    dispatch_context() {
        using ResolvedContextType = typename details::ContextResolver<InElement, Contexts...>::type;

        static_assert(not std::is_same<ResolvedContextType, details::EmptyContext>::value,
                      "Not found appropriate context type which holds `InElement` for processing");

        return static_cast<typename std::add_pointer<ResolvedContextType>::type>(this);
    }
};
} // namespace txml
#endif // SERIALIZER_DESERIALIZER_DISPATCHER_H
