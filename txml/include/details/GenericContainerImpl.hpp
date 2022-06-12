#ifndef XDXF_ARRAY_CONTAINER_NODE_HPP
#define XDXF_ARRAY_CONTAINER_NODE_HPP

#include <txml/include/details/fwd/GenericContainerImpl.h>

#include <txml/include/XMLProducible.hpp>
#include <txml/include/XMLNodeLeaf.hpp>
#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>

namespace txml
{
template<class Value>
XMLArrayContainerNode<Value>::XMLArrayContainerNode(typename aggregared_t::value_t &&val) :
    leaf_node(std::move(val))
{
}

template<class Value>
XMLArrayContainerNode<Value>::XMLArrayContainerNode(std::initializer_list<typename aggregared_t::value_t::value_type> list) :
    XMLArrayContainerNode(typename aggregared_t::value_t {list})
{
}

template<class Value>
template<class Fabric, class ...CreationArgs>
size_t XMLArrayContainerNode<Value>::create_from(CreationArgs&&... next_args)
{
    typename aggregared_t::value_t &arr = leaf_node.value();
    std::optional<Value> elem;
    do {
        elem = Fabric::template try_create<Value>(std::forward<CreationArgs>(next_args)...);
        if (elem) {
            arr.push_back(elem);
        }
    } while (elem);
    return arr.size();
}

template<class Value>
const typename XMLArrayContainerNode<Value>::aggregared_t::value_t &XMLArrayContainerNode<Value>::value() const
{
    return leaf_node.value();
}

template<class Value>
typename XMLArrayContainerNode<Value>::aggregared_t::value_t &XMLArrayContainerNode<Value>::value()
{
    return leaf_node.value();
}

template<class Value>
template<class Tracer>
void XMLArrayContainerNode<Value>::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<XMLArrayContainerNode<" << XMLArrayContainerNode<Value>::class_name() << ">>";

    const typename aggregared_t::value_t& array = leaf_node.value();
    for (const auto& elem : array)
    {
        if (elem)
        {
            elem->serialize(out, tracer);
        }
    }

    out << "</XMLArrayContainerNode<" << XMLArrayContainerNode<Value>::class_name() << ">>\n";
}

template<class Value>
template<class Tracer, class EndElementManipulator>
void XMLArrayContainerNode<Value>::serialize_elements(std::ostream &out, Tracer tracer,
                                                     EndElementManipulator sep) const
{
    tracer.trace(__FUNCTION__, " - XMLArrayContainerNode<", Value::class_name(), ">");
    const typename aggregared_t::value_t& array = leaf_node.value();
    for (const auto& elem : array)
    {
        if (elem)
        {
            elem->serialize(out, tracer);
        }
    }
}

template<class Value>
template<class Formatter, class Tracer>
void XMLArrayContainerNode<Value>::format_serialize_impl(Formatter &out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - XMLArrayContainerNode<", Value::class_name(), ">");
    const typename aggregared_t::value_t& array = leaf_node.value();
    for (const auto& elem : array)
    {
        if (elem)
        {
            elem->format_serialize(out, tracer);
        }
    }
}

template<class Value>
template<class Formatter, class Tracer>
void XMLArrayContainerNode<Value>::schema_serialize_impl(Formatter &out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - XMLArrayContainerNode<", Value::class_name(), ">");
    Value::schema_serialize(out, tracer);
}

template<class Value>
template<class Formatter, class Tracer>
size_t XMLArrayContainerNode<Value>::format_deserialize_impl(Formatter &in, Tracer tracer)
{
    tracer.trace("START deserialize Array<",Value::class_name(), ">");

    typename aggregared_t::value_t &arr = leaf_node.value();
    std::optional<Value> elem;

    size_t deserialized_count = 0;
    do {
        size_t array_index = arr.size();
        tracer.trace("Begin array index: ", array_index);
        elem = Value::format_deserialize(in, tracer);
        if (elem) {
            arr.push_back(elem);
            deserialized_count++;
        }
        tracer.trace("End array index: ", array_index);
    } while (elem);

    tracer.trace("START deserialize Array<",Value::class_name(), ">, deserialized count: ", deserialized_count);
    return deserialized_count;
}
} // namespace txml
#endif //XDXF_CREATOR_H
