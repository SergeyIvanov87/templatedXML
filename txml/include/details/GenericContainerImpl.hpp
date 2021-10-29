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
template<class Fabric, class ...CreationArgs>
bool XMLArrayContainerNode<Value>::create_from(CreationArgs&&... next_args)
{
    typename aggregared_t::value_t &arr = leaf_node.getValue();
    std::shared_ptr<Value> elem;
    do {
        elem = Fabric::template try_create<Value>(std::forward<CreationArgs>(next_args)...);
        if (elem) {
            arr.push_back(elem);
        }
    } while (elem);
    return !arr.empty();
}

template<class Value>
const typename XMLArrayContainerNode<Value>::aggregared_t::value_t &XMLArrayContainerNode<Value>::getValue() const
{
    return leaf_node.getValue();
}

template<class Value>
typename XMLArrayContainerNode<Value>::aggregared_t::value_t &XMLArrayContainerNode<Value>::getValue()
{
    return leaf_node.getValue();
}

template<class Value>
template<class Tracer>
void XMLArrayContainerNode<Value>::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<XMLArrayContainerNode<" << XMLArrayContainerNode<Value>::class_name() << ">>";

    const typename aggregared_t::value_t& array = leaf_node.getValue();
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
    const typename aggregared_t::value_t& array = leaf_node.getValue();
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
void XMLArrayContainerNode<Value>::format_serialize_elements(Formatter &out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - XMLArrayContainerNode<", Value::class_name(), ">");
    const typename aggregared_t::value_t& array = leaf_node.getValue();
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
void XMLArrayContainerNode<Value>::schema_serialize_elements(Formatter &out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - XMLArrayContainerNode<", Value::class_name(), ">");
    Value::schema_serialize(out, tracer);
}

template<class Value>
template<class Formatter, class Tracer>
size_t XMLArrayContainerNode<Value>::format_deserialize_elements(Formatter &in, Tracer tracer)
{
    tracer.trace("START deserialize Array<",Value::class_name(), ">");

    typename aggregared_t::value_t &arr = leaf_node.getValue();
    std::shared_ptr<Value> elem;

    size_t deserialized_count = 0;
    do {
        tracer.trace("Begin array index: ", arr.size());
        elem = Value::format_deserialize(in, tracer);
        if (elem) {
            arr.push_back(elem);
            deserialized_count++;
        }
        tracer.trace("End array index: ", arr.size());
    } while (elem);

    tracer.trace("START deserialize Array<",Value::class_name(), ">, deserialized count: ", deserialized_count);
    return deserialized_count;
}
} // namespace txml
#endif //XDXF_CREATOR_H
