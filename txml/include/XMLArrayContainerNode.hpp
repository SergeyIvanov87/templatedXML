#ifndef XDXF_ARRAY_CONTAINER_NODE_HPP
#define XDXF_ARRAY_CONTAINER_NODE_HPP

#include <txml/include/fwd/XMLArrayContainerNode.h>

#include <txml/include/XMLProducible.hpp>
#include <txml/include/XMLNodeLeaf.hpp>
#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>

namespace txml
{
template<class Value>
XMLArrayContainerNode<Value>::XMLArrayContainerNode(typename base::value_t &&val) :
    base(std::move(val))
{
}

template<class Value>
template<class Tracer>
std::shared_ptr<XMLArrayContainerNode<Value>>
XMLArrayContainerNode<Value>::create(TextReaderWrapper &reader, Tracer tracer)
{
    const std::string &name = reader.get_name();
    tracer.trace("Start creation XMLArrayContainerNode<", Value::class_name(), ">, got: '", name, "'");
    std::shared_ptr<XMLArrayContainerNode<Value>> ret;
    auto elem = producible_base::create(reader, tracer);
    if (elem)
    {
        std::vector<std::shared_ptr<Value>> data;
        const std::string name = elem->name();
        data.push_back(std::move(elem));
        ret.reset( new XMLArrayContainerNode<Value>(std::move(data)));
        tracer.trace("Init XMLArrayContainerNode<", Value::class_name(), "> with: '",
                     name , "', handle: ", ret.get());
    }
    return ret;
}

template<class Value>
const char *XMLArrayContainerNode<Value>::name() const noexcept
{
    return XMLArrayContainerNode::class_name();
}

template<class Value>
template<class Tracer>
void XMLArrayContainerNode<Value>::fill_impl(TextReaderWrapper &reader,
                                             Tracer tracer/* = Tracer()*/)
{
    auto elem = producible_base::create(reader, tracer);
    if (elem)
    {
        tracer.trace("Fill XMLArrayContainerNode<", Value::class_name(), "> with: '",
                     elem->name(), "', handle: ", this);
        base::getValue().push_back(std::move(elem));
    }
}

template<class Value>
template<class Tracer>
void XMLArrayContainerNode<Value>::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<XMLArrayContainerNode<" << XMLArrayContainerNode<Value>::class_name() << ">>";

    const typename base::value_t& array = base::getValue();
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
template<class Formatter, class Tracer>
void XMLArrayContainerNode<Value>::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - XMLArrayContainerNode<", class_name(), ">");
    Value::schema_serialize(out, tracer);
}

template<class Value>
template<class Formatter, class Tracer>
std::shared_ptr<XMLArrayContainerNode<Value>> XMLArrayContainerNode<Value>::format_deserialize_impl(Formatter& in, Tracer tracer)
{
    tracer.trace("Begin deserialize map 'XMLArrayContainerNode<", Value::class_name(), ">'");

    typename base::value_t arr;
    std::shared_ptr<Value> elem;
    do {
        tracer.trace("Begin array index: ", arr.size());
        elem = in.template map<Value>(tracer);
        if (elem) {
            arr.push_back(elem);
        }
        tracer.trace("End array index: ", arr.size());
    } while (elem);

    std::shared_ptr<XMLArrayContainerNode<Value>> ret;
    if (!arr.empty())
    {
        ret = std::make_shared<XMLArrayContainerNode<Value>>(std::move(arr));
    }
    tracer.trace("End deserialize map 'XMLArrayContainerNode<", Value::class_name(), ">', handle: ", ret.get());
    return ret;
}

template<class Value>
template<class Formatter, class Tracer>
void XMLArrayContainerNode<Value>::format_redeserialize_impl(Formatter& in, Tracer tracer)
{
    tracer.trace("Go on deserialize map 'XMLArrayContainerNode<", Value::class_name(),
                 ">', handle: ", this);

    typename base::value_t &arr = this->getValue();
    std::shared_ptr<Value> elem;
    do {
        tracer.trace("Begin array index: ", arr.size());
        elem = in.template map<Value>(tracer);
        if (elem) {
            arr.push_back(elem);
        }
        tracer.trace("End array index: ", arr.size());
    } while (elem);

    tracer.trace("Drop off deserialize map 'XMLArrayContainerNode<", Value::class_name(),
                 ">', handle: ", this);
}
} // namespace txml
#endif //XDXF_CREATOR_H
