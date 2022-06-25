#ifndef XML_NODE_HPP
#define XML_NODE_HPP

#include <algorithm>

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/XMLProducible.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>
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
    if (src.storage) //make copy
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
template<class ImplNEW,
         class ...SpecificContainedValues,
         class T>
XMLNode<TEMPL_ARGS_DEF>::XMLNode(const XMLNode<ImplNEW, SpecificContainedValues...> &src) :
    TracerHelper<Impl>(static_cast<const TracerHelper<Impl>&>(src))
{
    (this->template emplace<SpecificContainedValues>(src.template node<SpecificContainedValues>()), ...);
}

template<TEMPL_ARGS_DECL>
template<class ...SpecificContainedValues,
         class T>
XMLNode<TEMPL_ARGS_DEF>::XMLNode(const SpecificContainedValues & ...args)
{
    (this->template emplace<SpecificContainedValues>(args), ...);
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
    if (empty())
    {
        return false;
    }
    return std::get<ChildNode<T>>(*storage).has_value();
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
bool XMLNode<TEMPL_ARGS_DEF>::empty() const
{
    return ! storage.get();
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
    if (empty())
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
    auto new_node = std::make_optional<T>(std::forward<Args>(args)...);
    auto [ref, inserted] = this->template insert<T>(new_node);
    if (!inserted)
    {
        ref.get() = std::move(new_node);
    }
    return ref.get();
}



template<TEMPL_ARGS_DECL>
template<class T>
std::pair<std::reference_wrapper<typename XMLNode<TEMPL_ARGS_DEF>::ChildNode<T>>, bool>
XMLNode<TEMPL_ARGS_DEF>::insert(const ChildNode<T> &arg)
{
    if (!storage)
    {
        storage = std::make_shared<NodesStorage>();
    }

    std::reference_wrapper<ChildNode<T>> ref = std::get<ChildNode<T>>(*storage);
    bool inserted = false;
    if (!ref.get().has_value())
    {
        ref.get() = arg;
        inserted = true;
    }
    return  {ref, inserted};
}

template<TEMPL_ARGS_DECL>
template<class T>
std::pair<std::reference_wrapper<typename XMLNode<TEMPL_ARGS_DEF>::ChildNode<T>>, bool>
XMLNode<TEMPL_ARGS_DEF>::insert(ChildNode<T> &&arg)
{
    if (!storage)
    {
        storage = std::make_shared<NodesStorage>();
    }

    std::reference_wrapper<ChildNode<T>> ref = std::get<ChildNode<T>>(*storage);
    bool inserted = false;
    if (!ref.get().has_value())
    {
        ref.get() = std::move(arg);
        inserted = true;
    }
    return  {ref, inserted};
}

template<TEMPL_ARGS_DECL>
template<class T, class ...Args>
std::pair<std::reference_wrapper<typename XMLNode<TEMPL_ARGS_DEF>::ChildNode<std::decay_t<utils::decay_optional_t<std::decay_t<T>>>>>, bool>
XMLNode<TEMPL_ARGS_DEF>::emplace(Args &&...args)
{
    // TODO add static_cast for types compliance
    return this->insert(std::make_optional<std::decay_t<utils::decay_optional_t<std::decay_t<T>>>>(std::forward<Args>(args)...));
}

template<TEMPL_ARGS_DECL>
template<class T, class U>
std::pair<std::reference_wrapper<typename XMLNode<TEMPL_ARGS_DEF>::ChildNode<std::decay_t<utils::decay_optional_t<std::decay_t<T>>>>>, bool>
XMLNode<TEMPL_ARGS_DEF>::emplace(const std::optional<U> &node)
{
    // TODO add static_cast for types compliance
    using node_t = ChildNode<std::decay_t<utils::decay_optional_t<std::decay_t<T>>>>;
    if (node.has_value())
    {
        return this->insert(std::make_optional<std::decay_t<utils::decay_optional_t<std::decay_t<T>>>>(node.value()));
    }

    std::reference_wrapper<node_t> ref = std::get<node_t>(*storage);
    return  {ref, false};
}

template<TEMPL_ARGS_DECL>
template<class T, class U>
std::pair<std::reference_wrapper<typename XMLNode<TEMPL_ARGS_DEF>::ChildNode<std::decay_t<utils::decay_optional_t<std::decay_t<T>>>>>, bool>
XMLNode<TEMPL_ARGS_DEF>::emplace(std::optional<U> &&node)
{
    using node_t = ChildNode<std::decay_t<utils::decay_optional_t<std::decay_t<T>>>>;
    if (node.has_value())
    {
        return this->insert(std::make_optional<std::decay_t<utils::decay_optional_t<std::decay_t<T>>>>(std::move(node.value())));
    }

    std::reference_wrapper<node_t> ref = std::get<node_t>(*storage);
    return  {ref, false};
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
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - PERFORM");
    out.map(static_cast<const Impl&>(*this), tracer);
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - ACK: ", static_cast<const Impl&>(*this));
}


template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
std::optional<Impl> XMLNode<TEMPL_ARGS_DEF>::format_deserialize_request(Formatter& in, Tracer tracer)
{
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - PERFORM");
    auto ret = in.template map<Impl>(tracer);
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, ret ? " - ACK: " : " - NACK: ", ret);
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

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
size_t XMLNode<TEMPL_ARGS_DEF>::make_format_deserialize(Formatter &in, Tracer tracer)
{
    size_t deserialized_count_before = 0;
    if (!storage)
    {
        storage = std::make_shared<NodesStorage>();
        tracer.trace("'", Impl::class_name(), "' ", *static_cast<Impl*>(this)," - ", __FUNCTION__, " - START");
    }
    else
    {
        // get already deserialized element count
        deserialized_count_before = std::apply([](const std::optional<ContainedValues> &...element)
        {
            bool dispatchingResult[] {(element.has_value())...};
            return std::count(dispatchingResult, dispatchingResult + sizeof...(ContainedValues), true);
        }, *storage);
        tracer.trace("'", Impl::class_name(), "' ", *static_cast<Impl*>(this)," - ", __FUNCTION__, " - START: current deserialized elements: (", deserialized_count_before, "/", sizeof...(ContainedValues), ")");
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
        tracer.trace("'", Impl::class_name(), "' ", *static_cast<Impl*>(this)," - ", __FUNCTION__, " - FINISH");
        storage.reset();
        return 0;
    }

    tracer.trace("'", Impl::class_name(), "' ", *static_cast<Impl*>(this)," - ", __FUNCTION__, " - FINISH: deserialized elements: (", deserialized_count_after, "/", sizeof...(ContainedValues), ")");
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
