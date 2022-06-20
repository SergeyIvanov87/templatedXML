#ifndef XDXF_PRODUCIBLE_HPP
#define XDXF_PRODUCIBLE_HPP

#include <txml/include/fwd/XMLProducible.h>
#include <txml/include/utils.h>

#include <txml/include/engine/TextReaderWrap.hpp>

namespace txml
{
template<class Value>
template<class Tracer>
std::optional<Value> XMLProducible<Value>::create(TextReaderWrapper &reader, Tracer tracer)
{
    const std::string &name = reader.get_name();
    if (name != Value::class_name())
    {
        throw std::runtime_error(std::string("Expected: ") + std::string(Value::class_name()) +
                                 ", got: " + name);
    }

    TextReaderWrapper::NodeType nodeType = reader.get_node_type();
    if (nodeType != Value::class_node_type())
    {
        throw std::runtime_error(std::string("Expected node type: ") +
                                             to_string(TextReaderWrapper::NodeType::Element) +
                                             ", got: " + to_string(nodeType));
    }

    std::optional<Value> ret = std::make_optional<Value>();
    tracer.trace("Open tag '", Value::class_name(), "' handle: ", ret);

    {
        Tracer entered_tracer = tracer;
        bool initialized = false;
        while (reader.read())
        {
            const std::string& underlying_node_name = reader.get_name();
            nodeType = reader.get_node_type();

            entered_tracer.trace("extract tag: '", underlying_node_name, "', type: ", to_string(nodeType));
            if (underlying_node_name == Value::class_name() &&
                nodeType == TextReaderWrapper::NodeType::EndElement)
            {
                tracer.trace("Close tag '", Value::class_name(), "' handle: ", ret);
                break;
            }

            initialized |= ret->initialize(reader, tracer);
        }

        // if ret in container node, and no one sub-node is initialized, then throw away that node
        if (!initialized)
        {
            tracer.trace("SKIP tag '", Value::class_name(), "' handle: ", ret);
            ret.reset();
        }
    }
    return ret;
}


template<class Value>
template<class Tracer>
void XMLProducible<Value>::fill_impl(TextReaderWrapper &reader, Tracer tracer)
{
}
} // namespace txml
#endif //XDXF_PRODUCIBLE_HPP
