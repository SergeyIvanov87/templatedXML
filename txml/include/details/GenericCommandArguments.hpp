#ifndef GENERIC_COMMANDARGUMENTS_VALUE_HPP
#define GENERIC_COMMANDARGUMENTS_VALUE_HPP

#include <algorithm>
#include <type_traits>

#include <txml/include/details/GenericCommandArguments.h>

namespace txml
{
#define TEMPL_ARGS_DECL    class ...Arguments
#define TEMPL_ARGS_DEF     Arguments...

template<TEMPL_ARGS_DECL>
template<class T>
typename ArgumentContainerBase<TEMPL_ARGS_DEF>::template ArgumentPtr<T> ArgumentContainerBase<Arguments...>::getValue() const
{
    return std::get<ArgumentPtr<T>>(*storage);
}

template<TEMPL_ARGS_DECL>
const typename ArgumentContainerBase<TEMPL_ARGS_DEF>::Tuple& ArgumentContainerBase<Arguments...>::getValue() const
{
    return *storage;
}
template<TEMPL_ARGS_DECL>
typename ArgumentContainerBase<TEMPL_ARGS_DEF>::Tuple& ArgumentContainerBase<Arguments...>::getValue()
{
    return *storage;
}

template<TEMPL_ARGS_DECL>
template<class T>
typename ArgumentContainerBase<Arguments...>::ArgumentPtr<T>
ArgumentContainerBase<Arguments...>::set(ArgumentPtr<T> arg)
{
    if (arg.has_value() && !storage)
    {
        storage = std::make_shared<Tuple>();
    }
    std::get<ArgumentPtr<T>>(*storage) = arg;
    return arg;
}

template<TEMPL_ARGS_DECL>
template<class T, class ...Args>
typename ArgumentContainerBase<Arguments...>::ArgumentPtr<std::decay_t<T>>
ArgumentContainerBase<Arguments...>::emplace(Args &&...args)
{
    if (!storage)
    {
        storage = std::make_shared<Tuple>();
    }
    auto ret = std::make_shared<std::decay_t<T>>(std::forward<Args>(args)...);
    return set(ret);
}

template<TEMPL_ARGS_DECL>
template<class Fabric, class ...CreationArgs>
size_t ArgumentContainerBase<TEMPL_ARGS_DEF>::create_from(CreationArgs&&... next_args)
{
    Tuple tmp_storage;
    size_t created_nodes_count = std::apply([&next_args...](std::optional<Arguments> &...element) -> size_t
    {
        bool dispatchingResult[]
            {
                ((element = !element
                            ? Fabric::template try_create<Arguments>(std::forward<CreationArgs>(next_args)...)
                            : Fabric::template try_fill<Arguments>(element, std::forward<CreationArgs>(next_args)...)
                           ), element.has_value()/* true if created, or false*/)...
            };
        // success if one of element was created at least
        return std::count_if(dispatchingResult, dispatchingResult + sizeof...(Arguments), [] (bool val) {
            return val;
        });
    }, tmp_storage);

    if (created_nodes_count)
    {
        assert(!storage && "storage must be empty");
        storage = std::make_shared<Tuple>(std::move(tmp_storage));
    }
    return created_nodes_count;
}


template<TEMPL_ARGS_DECL>
template<class Tracer, class EndElementManipulator>
void ArgumentContainerBase<TEMPL_ARGS_DEF>::serialize_elements(std::ostream &out, Tracer tracer,
                                                     EndElementManipulator sep) const
{
    if (!storage)
    {
        return;
    }

    std::apply([&out, &tracer, &sep](const std::optional<Arguments> &...element)
    {
        bool dispatchingResult[]
            {
                (element ? element->serialize(out, tracer), out << sep, true : false)...
            };
        (void)dispatchingResult;
    }, *storage);
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
size_t ArgumentContainerBase<TEMPL_ARGS_DEF>::format_deserialize_elements(Formatter &in, Tracer tracer)
{
    if (!storage)
    {
        storage = std::make_shared<Tuple>();
    }
    tracer.trace("START deserialize element from types count: (", sizeof...(Arguments), "), storage: ", storage.get());
    size_t deserialized_count = std::apply([&in, &tracer](std::optional<Arguments> &...element)
    {
        bool dispatchingResult[]
            {
                ((element = !element
                            ? Arguments::format_deserialize(in, tracer)
                            : Arguments::format_redeserialize(element, in, tracer)
                            ), element.get() != nullptr/* true if created, or false*/)...
            };
        return std::count(dispatchingResult, dispatchingResult + sizeof...(Arguments), true);
    }, *storage);
    tracer.trace("FINISH deserialized elements: (", deserialized_count, " / ", sizeof...(Arguments), "), storage: ", storage.get());
    return deserialized_count;
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void ArgumentContainerBase<TEMPL_ARGS_DEF>::format_serialize_elements(Formatter &out, Tracer tracer) const
{
    if (!storage)
    {
        return;
    }
    std::apply([&out, &tracer](const std::optional<Arguments> &...element)
    {
        bool dispatchingResult[]
            {
                (element ? element->format_serialize(out, tracer), true : false)...
            };
        (void)dispatchingResult;
    }, *storage);
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void ArgumentContainerBase<TEMPL_ARGS_DEF>::schema_serialize_elements(Formatter &out, Tracer tracer)
{
    std::apply([&out, &tracer](const std::optional<Arguments> &...element)
    {
        bool dispatchingResult[]
            {
                (Arguments::schema_serialize(out, tracer), true)...
            };
        (void)dispatchingResult;
    }, Tuple {});
}

template<TEMPL_ARGS_DECL>
template<class Element, class Formatter, class Tracer>
void ArgumentContainerBase<TEMPL_ARGS_DEF>::schema_serialize_element(Formatter &out, Tracer tracer)
{
    static_assert(std::disjunction_v<std::is_same<Element, Arguments>...>, "Element type must be"
                  " one of Arguments type");
    Element::schema_serialize(out, tracer);
}

template<TEMPL_ARGS_DECL>
bool ArgumentContainerBase<TEMPL_ARGS_DEF>::has_value() const
{
    return storage;
}
#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif //GENERIC_COMMANDARGUMENTS_VALUE_HPP
