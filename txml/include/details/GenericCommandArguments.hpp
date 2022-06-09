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
bool ArgumentContainerBase<TEMPL_ARGS_DEF>::has_value() const
{
    if (has_data())
    {
        return std::get<ArgumentOptional<T>>(*storage).has_value();
    }
    return false;
}

template<TEMPL_ARGS_DECL>
template<class T>
const T& ArgumentContainerBase<Arguments...>::value() const
{
    if (!this->template has_value<T>())
    {
        this->template throw_exception<T>();
    }
    return std::get<ArgumentOptional<T>>(*storage).value();
}

template<TEMPL_ARGS_DECL>
template<class T>
T& ArgumentContainerBase<Arguments...>::value()
{
    if (!this->template has_value<T>())
    {
        this->template throw_exception<T>();
    }
    return std::get<ArgumentOptional<T>>(*storage).value();
}

template<TEMPL_ARGS_DECL>
bool ArgumentContainerBase<TEMPL_ARGS_DEF>::has_data() const
{
    return storage.get();
}

template<TEMPL_ARGS_DECL>
const typename ArgumentContainerBase<TEMPL_ARGS_DEF>::Tuple& ArgumentContainerBase<Arguments...>::data() const
{
    if (!has_value())
    {
        throw_exception();
    }
    return *storage;
}

template<TEMPL_ARGS_DECL>
typename ArgumentContainerBase<TEMPL_ARGS_DEF>::Tuple& ArgumentContainerBase<Arguments...>::data()
{
    return const_cast<Tuple&>(static_cast<const ArgumentContainerBase<TEMPL_ARGS_DEF>*>(this)->data());
}

template<TEMPL_ARGS_DECL>
template<class T>
const typename ArgumentContainerBase<TEMPL_ARGS_DEF>::template ArgumentOptional<T>& ArgumentContainerBase<Arguments...>::node() const
{
    if (!has_data())
    {
        static const ArgumentOptional<T> empty;
        return empty;
    }
    return std::get<ArgumentOptional<T>>(*storage);
}

template<TEMPL_ARGS_DECL>
template<class T, class ...Args>
typename ArgumentContainerBase<TEMPL_ARGS_DEF>::template ArgumentOptional<T>& ArgumentContainerBase<Arguments...>::node_or(Args &&...args)
{
    //TODO Return existing node OR create storage with node from args!!!!
    if (!this->template has_value<T>())
    {
        this->template throw_exception<T>();
    }
    return std::get<ArgumentOptional<T>>(*storage);
}


template<TEMPL_ARGS_DECL>
template<class T>
typename ArgumentContainerBase<Arguments...>::ArgumentOptional<T> &
ArgumentContainerBase<Arguments...>::insert(const ArgumentOptional<T> &arg, bool overwrite)
{
    if (arg.has_value() && !storage)
    {
        storage = std::make_shared<Tuple>();
    }
    std::get<ArgumentOptional<T>>(*storage) = arg;
    return std::get<ArgumentOptional<T>>(*storage);
}

template<TEMPL_ARGS_DECL>
template<class T>
typename ArgumentContainerBase<Arguments...>::ArgumentOptional<T> &
ArgumentContainerBase<Arguments...>::insert(ArgumentOptional<T> &&arg, bool overwrite)
{
    if (arg.has_value() && !storage)
    {
        storage = std::make_shared<Tuple>();
    }
    std::get<ArgumentOptional<T>>(*storage) = std::move(arg);
    return std::get<ArgumentOptional<T>>(*storage);
}

template<TEMPL_ARGS_DECL>
template<class T, class ...Args>
typename ArgumentContainerBase<Arguments...>::ArgumentOptional<std::decay_t<T>> &
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
    if (!storage)
    {
        storage = std::make_shared<Tuple>();
    }

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
    }, *storage);

    if (!created_nodes_count)
    {
        storage.reset();
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
size_t ArgumentContainerBase<TEMPL_ARGS_DEF>::format_deserialize_impl(Formatter &in, Tracer tracer)
{
    if (!storage)
    {
        storage = std::make_shared<Tuple>();//  ---->> HASH instead STORAGE!!! <<----
        tracer.trace("START deserialize element, allocate storage: ", storage.get());
    }
    tracer.trace("START deserialize element from types count: (", sizeof...(Arguments), "), storage: ", storage.get());
    size_t deserialized_count = std::apply([&in, &tracer](std::optional<Arguments> &...element)
    {
        bool dispatchingResult[]
            {
                ((element = !element
                            ? Arguments::format_deserialize(in, tracer)
                            : Arguments::format_redeserialize(element, in, tracer)
                            ), element.has_value()/* true if created, or false*/)...
            };
        return std::count(dispatchingResult, dispatchingResult + sizeof...(Arguments), true);
    }, *storage);
    tracer.trace("FINISH deserialized elements: (", deserialized_count, " / ", sizeof...(Arguments), "), storage: ", storage.get());
    if (!deserialized_count)
    {
        tracer.trace("FINISH deserialize element, delete storage: ", storage.get());
        storage.reset();
    }
    return deserialized_count;
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void ArgumentContainerBase<TEMPL_ARGS_DEF>::format_serialize_impl(Formatter &out, Tracer tracer) const
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
void ArgumentContainerBase<TEMPL_ARGS_DEF>::schema_serialize_impl(Formatter &out, Tracer tracer)
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
void ArgumentContainerBase<TEMPL_ARGS_DEF>::schema_serialize_impl(Formatter &out, Tracer tracer)
{
    static_assert(std::disjunction_v<std::is_same<Element, Arguments>...>, "Element type must be"
                  " one of Arguments type");
    Element::schema_serialize(out, tracer);
}

/*
template<TEMPL_ARGS_DECL>
size_t ArgumentContainerBase<TEMPL_ARGS_DEF>::hash() const
{
    return reinterpret_cast<size_t>(storage.get());
}*/

template<TEMPL_ARGS_DECL>
[[ noreturn ]] void ArgumentContainerBase<TEMPL_ARGS_DEF>::throw_exception() const
{
    std::stringstream ss;
    ss << "<";
    (ss << ... << Arguments::class_name());
    ss << "> hash: "/* <<  hash() << */" has no value";
    throw std::invalid_argument(ss.str());
}

template<TEMPL_ARGS_DECL>
template<class T>
[[ noreturn ]] void ArgumentContainerBase<TEMPL_ARGS_DEF>::throw_exception() const
{
    std::stringstream ss;
    ss << "<";
    (ss << ... << Arguments::class_name());
    ss << "> hash: "/* <<  hash() << */" has no value: " << T::class_name();
    throw std::invalid_argument(ss.str());
}

#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif //GENERIC_COMMANDARGUMENTS_VALUE_HPP
