#ifndef GENERIC_COMMANDARGUMENTS_VALUE_HPP
#define GENERIC_COMMANDARGUMENTS_VALUE_HPP

#include "details/GenericCommandArguments.h"

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
void ArgumentContainerBase<TEMPL_ARGS_DEF>::create_from(CreationArgs&&... next_args)
{
    std::apply([&next_args...](std::shared_ptr<Arguments> &...element)
    {
        bool dispatchingResult[]
            {
                ((element = !element
                            ? Fabric::template try_create<Arguments>(std::forward<CreationArgs>(next_args)...)
                            : Fabric::template try_fill<Arguments>(element, std::forward<CreationArgs>(next_args)...)
                           ), true)...
            };
        (void)dispatchingResult;
    }, storage);
}

template<TEMPL_ARGS_DECL>
template<class Argument, class Tracer>
void ArgumentContainerBase<TEMPL_ARGS_DEF>::dump(std::ostream &out, Tracer tracer) const
{
    this->get<Argument>()->dump(out, tracer);
}

template<TEMPL_ARGS_DECL>
template<class Tracer, class EndElementManipulator>
void ArgumentContainerBase<TEMPL_ARGS_DEF>::dump_all(std::ostream &out, Tracer tracer,
                                                     EndElementManipulator sep) const
{
    std::apply([&out, &tracer, &sep](const std::shared_ptr<Arguments> &...element)
    {
        bool dispatchingResult[]
            {
                (element ? element->publish_impl(out, tracer), out << sep, true : false)...
            };
        (void)dispatchingResult;
    }, storage);
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void ArgumentContainerBase<TEMPL_ARGS_DEF>::format_dump_all(Formatter &out, Tracer tracer) const
{
    std::apply([&out, &tracer](const std::shared_ptr<Arguments> &...element)
    {
        bool dispatchingResult[]
            {
                (element ? element->format_publish_impl(out, tracer), true : false)...
            };
        (void)dispatchingResult;
    }, storage);
}


#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
#endif //GENERIC_COMMANDARGUMENTS_VALUE_HPP
