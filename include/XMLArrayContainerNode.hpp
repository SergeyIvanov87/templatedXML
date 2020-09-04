#ifndef XDXF_ARRAY_CONTAINER_NODE_HPP
#define XDXF_ARRAY_CONTAINER_NODE_HPP

#include "XMLArrayContainerNode.h"

template<class Value>
XMLArrayContainerNode<Value>::XMLArrayContainerNode(typename base::value_t &&val) :
    base(std::move(val))
{
}

template<class Value>
template<class Tracer>
std::shared_ptr<XMLArrayContainerNode<Value>>
XMLArrayContainerNode<Value>::create_impl(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer)
{
    tracer.trace("Start creation XMLArrayContainerNode<", Value::class_name(), ">, got: '", name, "'");
    std::shared_ptr<XMLArrayContainerNode<Value>> ret;
    auto elem = producible_base::create_impl(name, depth, reader, tracer);
    if (elem)
    {
        std::vector<std::shared_ptr<Value>> data;
        const std::string name = elem->name();
        data.push_back(std::move(elem));
        ret.reset( new XMLArrayContainerNode<Value>(std::move(data)));
        tracer.trace("Init XMLArrayContainerNode<", Value::class_name(), "> with: '",
                     name , "', handle: ", reinterpret_cast<size_t>(ret.get()));
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
void XMLArrayContainerNode<Value>::fill_impl(std::string &name, int &depth,
                                               xmlpp::TextReader &reader,
                                               Tracer tracer/* = Tracer()*/)
{
    auto elem = producible_base::create_impl(name, depth, reader, tracer);
    if (elem)
    {
        tracer.trace("Fill XMLArrayContainerNode<", Value::class_name(), "> with: '",
                     elem->name(), "', handle: ", reinterpret_cast<size_t>(this));
        base::getValue().push_back(std::move(elem));
    }
}

#endif //XDXF_CREATOR_H
