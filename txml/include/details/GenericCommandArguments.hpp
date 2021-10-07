#ifndef GENERIC_COMMANDARGUMENTS_VALUE_HPP
#define GENERIC_COMMANDARGUMENTS_VALUE_HPP

#include <txml/include/details/GenericCommandArguments.h>

namespace txml
{
#define TEMPL_ARGS_DECL    class ...Arguments
#define TEMPL_ARGS_DEF     Arguments...

template<TEMPL_ARGS_DECL>
template<class T>
typename ArgumentContainerBase<TEMPL_ARGS_DEF>::template ArgumentPtr<T> ArgumentContainerBase<Arguments...>::get() const
{
    return std::get<ArgumentPtr<T>>(storage);
}


template<TEMPL_ARGS_DECL>
template<class T>
void ArgumentContainerBase<Arguments...>::set(ArgumentPtr<T> arg)
{
    std::get<ArgumentPtr<T>>(storage) = arg;
}

template<TEMPL_ARGS_DECL>
template<class Fabric, class ...CreationArgs>
bool ArgumentContainerBase<TEMPL_ARGS_DEF>::create_from(CreationArgs&&... next_args)
{
    return std::apply([&next_args...](std::shared_ptr<Arguments> &...element) -> bool
    {
        bool dispatchingResult[]
            {
                ((element = !element
                            ? Fabric::template try_create<Arguments>(std::forward<CreationArgs>(next_args)...)
                            : Fabric::template try_fill<Arguments>(element, std::forward<CreationArgs>(next_args)...)
                           ), element.get() != nullptr/* true if created, or false*/)...
            };
        // success if one of element was created at least
        return std::any_of(dispatchingResult, dispatchingResult + sizeof...(Arguments), [] (bool val) {
            return val;
        });
    }, storage);
}

template<TEMPL_ARGS_DECL>
template<class Argument, class Tracer>
void ArgumentContainerBase<TEMPL_ARGS_DEF>::serialize_impl(std::ostream &out, Tracer tracer) const
{
    this->get<Argument>()->serialize_impl(out, tracer);
}

template<TEMPL_ARGS_DECL>
template<class Tracer, class EndElementManipulator>
void ArgumentContainerBase<TEMPL_ARGS_DEF>::serialize_elements(std::ostream &out, Tracer tracer,
                                                     EndElementManipulator sep) const
{
    std::apply([&out, &tracer, &sep](const std::shared_ptr<Arguments> &...element)
    {
        bool dispatchingResult[]
            {
                (element ? element->serialize(out, tracer), out << sep, true : false)...
            };
        (void)dispatchingResult;
    }, storage);
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void ArgumentContainerBase<TEMPL_ARGS_DEF>::format_deserialize_elements(Formatter &in, Tracer tracer)
{
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void ArgumentContainerBase<TEMPL_ARGS_DEF>::format_serialize_elements(Formatter &out, Tracer tracer) const
{
    std::apply([&out, &tracer](const std::shared_ptr<Arguments> &...element)
    {
        bool dispatchingResult[]
            {
                (element ? element->format_serialize(out, tracer), true : false)...
            };
        (void)dispatchingResult;
    }, storage);
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void ArgumentContainerBase<TEMPL_ARGS_DEF>::schema_serialize_elements(Formatter &out, Tracer tracer)
{
    std::apply([&out, &tracer](const std::shared_ptr<Arguments> &...element)
    {
        bool dispatchingResult[]
            {
                (Arguments::schema_serialize(out, tracer), true)...
            };
        (void)dispatchingResult;
    }, Tuple {});
}
#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif //GENERIC_COMMANDARGUMENTS_VALUE_HPP
