#ifndef XDXF_CREATABLE_HPP
#define XDXF_CREATABLE_HPP

#include <txml/XMLProducible.h>
#include <txml/utils.h>

template<class Value>
template<class Tracer>
std::shared_ptr<Value> XMLProducible<Value>::create_impl(std::string &name, TextReaderWrapper &reader, Tracer tracer)
{
    if (name != Value::class_name())
    {
        throw std::runtime_error(std::string("Expected: ") + Value::class_name() +
                                 ", got: " + name);
    }

    TextReaderWrapper::NodeType nodeType = reader.get_node_type();
    if (nodeType != Value::class_node_type())
    {
        throw std::runtime_error(std::string("Expected node type: ") +
                                             to_string(TextReaderWrapper::NodeType::Element) +
                                             ", got: " + to_string(nodeType));
    }

    std::shared_ptr<Value> ret = std::make_shared<Value>();
    tracer.trace("Open tag '", Value::class_name(), "' handle: ", reinterpret_cast<size_t>(ret.get()));

    {
        Tracer entered_tracer = tracer;
        while (reader.read())
        {
            name = reader.get_name();
            nodeType = reader.get_node_type();

            entered_tracer.trace("extract tag: '", name, "', type: ", to_string(nodeType));
            if (name == Value::class_name() &&
                reader.get_node_type() == TextReaderWrapper::NodeType::EndElement)
            {
                tracer.trace("Close tag '", Value::class_name(), "' handle: ", reinterpret_cast<size_t>(ret.get()));
                break;
            }

            ret->initialize(name, reader, tracer);
        }
    }
    return ret;
}


template<class Value>
template<class Tracer>
void XMLProducible<Value>::fill_impl(std::string &name, TextReaderWrapper &reader, Tracer tracer)
{
}
#endif //XDXF_CREATABLE_HPP
