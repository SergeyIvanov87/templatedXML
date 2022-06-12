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
