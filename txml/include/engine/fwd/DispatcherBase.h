#ifndef IO_DISPATCHER_BASE_H
#define IO_DISPATCHER_BASE_H

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
} // namespace details


template<class ...Contexts>
struct DispatcherBase : public Contexts...
{
    template<class ...Args>
    DispatcherBase(Args &&...args) :
        Contexts{std::forward<Args>(args)...}...
    {
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
#endif // IO_DISPATCHER_BASE_H
