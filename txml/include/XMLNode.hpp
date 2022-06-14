#ifndef XML_NODE_HPP
#define XML_NODE_HPP

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/XMLProducible.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>
#include <txml/include/details/GenericCommandArguments.hpp>
#include <txml/include/engine/TextReaderWrap.hpp>
#include <txml/include/engine/TracerHelper.hpp>

namespace txml
{
#define TEMPL_ARGS_DECL    class Impl, class ...ContainedValues
#define TEMPL_ARGS_DEF     Impl, ContainedValues...

template<TEMPL_ARGS_DECL>
XMLNode<TEMPL_ARGS_DEF>::XMLNode(const XMLNode &src) :
    TracerHelper<Impl>(src)
{
    if (src.storage)
    {
        storage.reset(new NodesStorage(*src.storage));
    }
}

template<TEMPL_ARGS_DECL>
XMLNode<TEMPL_ARGS_DEF>::XMLNode(XMLNode &&src) :
    TracerHelper<Impl>(static_cast<TracerHelper<Impl>&&>(src))
{
    storage = std::move(src.storage);
}

template<TEMPL_ARGS_DECL>
template<class ...SpecificContainedValues>
XMLNode<TEMPL_ARGS_DEF>::XMLNode(const SpecificContainedValues & ...args)
{
    (this->template emplace<SpecificContainedValues>(args), ...);
}

template<TEMPL_ARGS_DECL>
template<class ...SpecificContainedValues>
XMLNode<TEMPL_ARGS_DEF>::XMLNode(const std::optional<SpecificContainedValues> & ...args)
{
    ((args.has_value() ? this->template emplace<SpecificContainedValues>(args),true : false), ...);
}

template<TEMPL_ARGS_DECL>
XMLNode<TEMPL_ARGS_DEF> &XMLNode<TEMPL_ARGS_DEF>::operator=(const XMLNode &src)
{
    if (this != &src)
    {
        if (src.storage)
        {
            storage.reset(new NodesStorage(*src.storage));
        }
        else
        {
            storage.reset();
        }
        static_cast<TracerHelper<Impl>&>(*this) = static_cast<const TracerHelper<Impl>&>(src);
    }
    return *this;
}

template<TEMPL_ARGS_DECL>
XMLNode<TEMPL_ARGS_DEF> &XMLNode<TEMPL_ARGS_DEF>::operator=(XMLNode &&src)
{
    if (this != &src)
    {
        storage = std::move(src.storage);
        static_cast<TracerHelper<Impl>&>(*this) = static_cast<TracerHelper<Impl>&&>(src);
    }
    return *this;
}

// Nodes operation interface implementation
template<TEMPL_ARGS_DECL>
template<class T>
bool XMLNode<TEMPL_ARGS_DEF>::has_value() const
{
    if (has_data())
    {
        return std::get<ChildNode<T>>(*storage).has_value();
    }
    return false;
}

template<TEMPL_ARGS_DECL>
template<class T>
const T& XMLNode<TEMPL_ARGS_DEF>::value() const
{
    if (!this->template has_value<T>())
    {
        this->template throw_exception<T>();
    }
    return std::get<ChildNode<T>>(*storage).value();
}

template<TEMPL_ARGS_DECL>
template<class T>
T& XMLNode<TEMPL_ARGS_DEF>::value()
{
    if (!this->template has_value<T>())
    {
        this->template throw_exception<T>();
    }
    return std::get<ChildNode<T>>(*storage).value();
}

template<TEMPL_ARGS_DECL>
bool XMLNode<TEMPL_ARGS_DEF>::has_data() const
{
    return storage.get();
}

template<TEMPL_ARGS_DECL>
const typename XMLNode<TEMPL_ARGS_DEF>::NodesStorage& XMLNode<TEMPL_ARGS_DEF>::data() const
{
    if (!has_value())
    {
        throw_exception();
    }
    return *storage;
}

template<TEMPL_ARGS_DECL>
typename XMLNode<TEMPL_ARGS_DEF>::NodesStorage& XMLNode<TEMPL_ARGS_DEF>::data()
{
    return const_cast<NodesStorage&>(static_cast<const XMLNode<TEMPL_ARGS_DEF>*>(this)->data());
}

template<TEMPL_ARGS_DECL>
template<class T>
const typename XMLNode<TEMPL_ARGS_DEF>::template ChildNode<T>& XMLNode<TEMPL_ARGS_DEF>::node() const
{
    if (!has_data())
    {
        static const ChildNode<T> empty;
        return empty;
    }
    return std::get<ChildNode<T>>(*storage);
}

template<TEMPL_ARGS_DECL>
template<class T, class ...Args>
typename XMLNode<TEMPL_ARGS_DEF>::template ChildNode<T>& XMLNode<TEMPL_ARGS_DEF>::node_or(Args &&...args)
{
    //TODO Return existing node OR create storage with node from args!!!!
    if (!this->template has_value<T>())
    {
        this->template throw_exception<T>();
    }
    return std::get<ChildNode<T>>(*storage);
}



template<TEMPL_ARGS_DECL>
template<class T>
typename XMLNode<TEMPL_ARGS_DEF>::ChildNode<T> &
XMLNode<TEMPL_ARGS_DEF>::insert(const ChildNode<T> &arg, bool overwrite)
{
    if (arg.has_value() && !storage)
    {
        storage = std::make_shared<NodesStorage>();
    }
    std::get<ChildNode<T>>(*storage) = arg;
    return std::get<ChildNode<T>>(*storage);
}

template<TEMPL_ARGS_DECL>
template<class T>
typename XMLNode<TEMPL_ARGS_DEF>::ChildNode<T> &
XMLNode<TEMPL_ARGS_DEF>::insert(ChildNode<T> &&arg, bool overwrite)
{
    if (arg.has_value() && !storage)
    {
        storage = std::make_shared<NodesStorage>();
    }
    std::get<ChildNode<T>>(*storage) = std::move(arg);
    return std::get<ChildNode<T>>(*storage);
}

template<TEMPL_ARGS_DECL>
template<class T, class ...Args>
typename XMLNode<TEMPL_ARGS_DEF>::ChildNode<std::decay_t<T>> &
XMLNode<TEMPL_ARGS_DEF>::emplace(Args &&...args)
{
    if (!storage)
    {
        storage = std::make_shared<NodesStorage>();
    }
    auto ret = std::make_shared<std::decay_t<T>>(std::forward<Args>(args)...);
    return set(ret);
}



template<TEMPL_ARGS_DECL>
template<class Tracer>
bool XMLNode<TEMPL_ARGS_DEF>::initialize(TextReaderWrapper &reader, Tracer tracer/* = Tracer()*/)
{
    const std::string &name = reader.get_name();
    tracer.trace("try saturate node '", Impl::class_name(), "' with: '", name,
                 "', expected count: ", sizeof...(ContainedValues));
    size_t ret = this->template create_from<XMLCreator>(reader, tracer);
    tracer.trace("saturation node '", Impl::class_name(), "' with: '", name,
                "', ratio got: ", ret, "/", sizeof...(ContainedValues));
    return ret;
}

template<TEMPL_ARGS_DECL>
template<class Fabric, class ...CreationArgs>
size_t XMLNode<TEMPL_ARGS_DEF>::create_from(CreationArgs&&... next_args)
{
    if (!storage)
    {
        storage = std::make_shared<NodesStorage>();
    }

    size_t created_nodes_count = std::apply([&next_args...](std::optional<ContainedValues> &...element) -> size_t
    {
        bool dispatchingResult[]
            {
                ((element = !element
                            ? Fabric::template try_create<ContainedValues>(std::forward<CreationArgs>(next_args)...)
                            : Fabric::template try_fill<ContainedValues>(element, std::forward<CreationArgs>(next_args)...)
                           ), element.has_value()/* true if created, or false*/)...
            };
        // success if one of element was created at least
        return std::count_if(dispatchingResult, dispatchingResult + sizeof...(ContainedValues), [] (bool val) {
            return val;
        });
    }, *storage);

    if (!created_nodes_count)
    {
        storage.reset();
    }
    return created_nodes_count;
}

/*
template<TEMPL_ARGS_DECL>
void XMLNode<TEMPL_ARGS_DEF>::make_xml_serialize(std::ostream &out) const
{
    Container::serialize_elements(out);
}
*/
template<TEMPL_ARGS_DECL>
template<class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::make_xml_serialize(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Impl::class_name() << ">";
    if (!storage)
    {
        return;
    }

    std::apply([&out, &tracer](const std::optional<ContainedValues> &...element)
    {
        bool dispatchingResult[]
            {
                (element ? element->xml_serialize(out, tracer), out << txml::no_sep, true : false)...
            };
        (void)dispatchingResult;
    }, *storage);
    out << "</" << Impl::class_name() << ">\n";
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::format_serialize_request(Formatter& out, Tracer tracer) const
{
    tracer.trace("map node '", Impl::class_name(), "'");
    out.map(static_cast<const Impl&>(*this), tracer);
    tracer.trace("unmap node '", Impl::class_name(), "'");
}


template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
std::optional<Impl> XMLNode<TEMPL_ARGS_DEF>::format_deserialize_request(Formatter& in, Tracer tracer)
{
    tracer.trace("Begin deserialize map '", Impl::class_name(), "'");
    auto ret = in.template map<Impl>(tracer);
    tracer.trace("End deserialize map '", Impl::class_name(), "', handle: ", ret);
    return ret;
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::format_redeserialize_request(Formatter& in, Tracer tracer)
{
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::schema_serialize_request(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", Impl::class_name());
    out.template map<Impl>(tracer);
}

//
template<TEMPL_ARGS_DECL>
template<class Tracer, class EndElementManipulator>
void XMLNode<TEMPL_ARGS_DEF>::serialize_elements(std::ostream &out, Tracer tracer,
                                                 EndElementManipulator sep) const
{
    if (!storage)
    {
        return;
    }

    std::apply([&out, &tracer, &sep](const std::optional<ContainedValues> &...element)
    {
        bool dispatchingResult[]
            {
                (element ? element->xml_serialize(out, tracer), out << sep, true : false)...
            };
        (void)dispatchingResult;
    }, *storage);
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
size_t XMLNode<TEMPL_ARGS_DEF>::make_format_deserialize(Formatter &in, Tracer tracer)
{
    size_t deserialized_count_before = 0;
    if (!storage)
    {
        storage = std::make_shared<NodesStorage>();
        tracer.trace("START: deserialize element, tag: ", *static_cast<Impl*>(this)); // TODO no need to invoke hash directly!!!! performance pessimisation
        // TODO IT must be done from StdoutTracer specializarion!!!!!
    }
    else
    {
        // get already deserialized element count
        deserialized_count_before = std::apply([](const std::optional<ContainedValues> &...element)
        {
            bool dispatchingResult[] {(element.has_value())...};
            return std::count(dispatchingResult, dispatchingResult + sizeof...(ContainedValues), true);
        }, *storage);
        tracer.trace("START: current deserialized elements: (", deserialized_count_before, "/", sizeof...(ContainedValues), "), tag: ", *static_cast<Impl*>(this));
    }

    // apply recursion
    size_t deserialized_count_after = std::apply([&in, &tracer](std::optional<ContainedValues> &...element)
    {
        bool dispatchingResult[]
            {
                ((element = !element
                            ? ContainedValues::format_deserialize(in, tracer)
                            : ContainedValues::format_redeserialize(element, in, tracer)
                            ), element.has_value()/* true if created, or false*/)...
            };
        return std::count(dispatchingResult, dispatchingResult + sizeof...(ContainedValues), true);
    }, *storage);


    if (!deserialized_count_after)
    {
        tracer.trace("FINISH: deserialize element, delete storage, tag: ", *static_cast<Impl*>(this));
        storage.reset();
        return 0;
    }

    tracer.trace("FINISH: total deserialized elements: (", deserialized_count_after, "/", sizeof...(ContainedValues), "), tag: ", *static_cast<Impl*>(this));
    return deserialized_count_after - deserialized_count_before;
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::make_format_serialize(Formatter &out, Tracer tracer) const
{
    if (!storage)
    {
        return;
    }
    std::apply([&out, &tracer](const std::optional<ContainedValues> &...element)
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
void XMLNode<TEMPL_ARGS_DEF>::make_schema_serialize(Formatter &out, Tracer tracer)
{
    std::apply([&out, &tracer](const std::optional<ContainedValues> &...element)
    {
        bool dispatchingResult[]
            {
                (ContainedValues::schema_serialize(out, tracer), true)...
            };
        (void)dispatchingResult;
    }, NodesStorage {});
}

template<TEMPL_ARGS_DECL>
template<class Element, class Formatter, class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::make_schema_serialize(Formatter &out, Tracer tracer)
{
    static_assert(std::disjunction_v<std::is_same<Element, ContainedValues>...>, "Element type must be"
                  " one of ContainedValues type");
    Element::schema_serialize(out, tracer);
}


template<TEMPL_ARGS_DECL>
[[ noreturn ]] void XMLNode<TEMPL_ARGS_DEF>::throw_exception() const
{
    std::stringstream ss;
    ss << "<" << Impl::class_name() << ",";
    (ss << ... << ContainedValues::class_name());
    ss << "> hash: " <<  this->hash() << " has no value";
    throw std::invalid_argument(ss.str());
}

template<TEMPL_ARGS_DECL>
template<class T>
[[ noreturn ]] void XMLNode<TEMPL_ARGS_DEF>::throw_exception() const
{
    std::stringstream ss;
    ss << "<" << Impl::class_name() << ",";
    (ss << ... << ContainedValues::class_name());
    ss << "> hash: " <<  this->hash() << " has no value: " << T::class_name();
    throw std::invalid_argument(ss.str());
}



#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif //XML_NODE_HPP
