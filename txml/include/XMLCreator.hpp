#ifndef XDXF_CREATOR_HPP
#define XDXF_CREATOR_HPP

#include <txml/include/fwd/XMLCreator.h>

#include <txml/include/engine/TextReaderWrap.hpp>
#include <txml/include/utils.h>

namespace txml
{
template<class Value, class Tracer>
std::shared_ptr<Value> XMLCreator::try_create(std::string &name,
                                               TextReaderWrapper &reader,
                                               Tracer tracer/* = Tracer()*/)
{
    std::shared_ptr<Value> ret;
    if (name != Value::class_name())
    {
        return ret;
    }

    TextReaderWrapper::NodeType nodeType = reader.get_node_type();
    tracer.trace("Found '", to_string(nodeType), "', tag name: '", name, "'");

    if (nodeType == Value::class_node_type())
    {
        // open node
        if(reader.has_attributes())
        {
            tracer.trace("attributes: ");
            reader.move_to_first_attribute();
            do
            {
                tracer.trace("  ", reader.get_name(), ": ", reader.get_value());;
            } while(reader.move_to_next_attribute());
            reader.move_to_element();
        }
        else
        {
            tracer.trace("no attributes");
        }


        ret = Value::create_impl(name, reader, tracer);
    }

    return ret;
}


template<class Value, class Tracer>
std::shared_ptr<Value> XMLCreator::try_fill(std::shared_ptr<Value> to_fill,
                                            std::string &name,
                                            TextReaderWrapper &reader,
                                            Tracer tracer/* = Tracer()*/)
{
    if (name == Value::class_name())
    {
        if (to_fill)
        {
            tracer.trace("fill xml array container with: ", reader.get_name());
            to_fill->fill_impl(name, reader, tracer);
        }
        else
        {
            tracer.trace("Incorrect usage for: ", __PRETTY_FUNCTION__);
            assert(false && __PRETTY_FUNCTION__);
        }
    }
    return to_fill;
}
} // namespace txml
#endif //XDXF_CREATOR_H
