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
        storage = std::make_shared<Tuple>();
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
void XMLNode<TEMPL_ARGS_DEF>::serialize_impl(std::ostream &out) const
{
    Container::serialize_elements(out);
}
*/
template<TEMPL_ARGS_DECL>
template<class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
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
                (element ? element->serialize(out, tracer), out << txml::no_sep, true : false)...
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
                (element ? element->serialize(out, tracer), out << sep, true : false)...
            };
        (void)dispatchingResult;
    }, *storage);
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
size_t XMLNode<TEMPL_ARGS_DEF>::format_deserialize_impl(Formatter &in, Tracer tracer)
{
    size_t deserialized_count_before = 0;
    if (!storage)
    {
        storage = std::make_shared<Tuple>();
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
void XMLNode<TEMPL_ARGS_DEF>::format_serialize_impl(Formatter &out, Tracer tracer) const
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
void XMLNode<TEMPL_ARGS_DEF>::schema_serialize_impl(Formatter &out, Tracer tracer)
{
    std::apply([&out, &tracer](const std::optional<ContainedValues> &...element)
    {
        bool dispatchingResult[]
            {
                (ContainedValues::schema_serialize(out, tracer), true)...
            };
        (void)dispatchingResult;
    }, Tuple {});
}

template<TEMPL_ARGS_DECL>
template<class Element, class Formatter, class Tracer>
void XMLNode<TEMPL_ARGS_DEF>::schema_serialize_impl(Formatter &out, Tracer tracer)
{
    static_assert(std::disjunction_v<std::is_same<Element, ContainedValues>...>, "Element type must be"
                  " one of ContainedValues type");
    Element::schema_serialize(out, tracer);
}

#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif //XML_NODE_HPP
