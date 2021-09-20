#ifndef EMPTY_HPP
#define EMPTY_HPP

#include <txml/XMLNodeLeaf.hpp>
#include <txml/XMLSerializable.hpp>

#include <txml/applications/fb2/Empty.h>

Empty::Empty(std::string&& str) : base(std::move(str))
{
}

const char *Empty::name() const noexcept
{
    return class_name();
}


template<class Tracer>
void Empty::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Empty::class_name() << getValue() << " -->\n";
}

template<class Tracer>
std::shared_ptr<Empty> Empty::create_impl(std::string &name, TextReaderWrapper &reader, Tracer tracer)
{
    std::shared_ptr<Empty> ret;

    if (name != Empty::class_name())
    {
        throw std::runtime_error(std::string("Expected: ") + Empty::class_name() +
                                 ", got: " + name);
    }

    TextReaderWrapper::NodeType nodeType = reader.get_node_type();
    if (nodeType != Empty::class_node_type())
    {
        tracer.trace("<skip '", Empty::class_name(), "' for node type: ", to_string(nodeType),
                     ", expected node type: ", to_string(TextReaderWrapper::NodeType::Text));
        return ret;
    }


    tracer.trace("Open tag '", Empty::class_name(), "'");
    if (reader.has_value())
    {
        const std::string& tmp_value = reader.get_value();
        auto it = tmp_value.begin();
        if (*it == '\r' or *it == '\n')
        {
            ++it;
        }
        ret.reset( new Empty(std::string(it, tmp_value.end())));
        tracer.trace("Value: '", ret->getValue(), "'");
    }

    tracer.trace("Close tag '", Empty::class_name(), "'");
    return ret;
}
#endif //EMPTY_HPP
