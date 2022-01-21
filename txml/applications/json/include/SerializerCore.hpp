#ifndef TXML_APPLICATION_JSON_IOCORE_HPP
#define TXML_APPLICATION_JSON_IOCORE_HPP

#include <txml/applications/json/include/fwd/SerializerCore.h>
#include <txml/include/utils/specific_tracer/EmptyTracer.hpp>

namespace json
{
inline SerializerCore::SerializerCore(std::shared_ptr<std::stack<json_core_t>> external_object_stack) :
    json_object_stack_helper(external_object_stack)
{
}

inline SerializerCore::~SerializerCore() = default;

template<class Tracer>
inline SerializerCore::json_core_t SerializerCore::finalize(Tracer tracer) const
{
    json_core_t out;

    size_t awaiting_element_count = json_object_stack_helper->size();
    if (awaiting_element_count == 1)
    {
        tracer.trace(__FUNCTION__, " - from single object, chose ",
                     utils::json_type_to_cstring(json_core_t::value_t::object), " as result holder");

        json_core_t &serialized_element = json_object_stack_helper->top();
        out = json_core_t::object();
        out.insert(serialized_element.begin(), serialized_element.end());
        //json_object_stack_helper->pop();
    }
    else if (awaiting_element_count > 1)
    {
        tracer.trace(__FUNCTION__, " - from object count: ", awaiting_element_count, ", chose ",
                     utils::json_type_to_cstring(json_core_t::value_t::array), " as result holder");
/*
        out = json_core_t::array();
        for (size_t i = 0; i < json_object_stack_helper->size(); i++)
        {
            json_core_t &serialized_element = json_object_stack_helper->top();
            tracer.trace(__FUNCTION__, " - merge: ", serialized_element.dump(),
                                   ", to: ", out.dump());
            out.insert(out.end(),serialized_element.begin(), serialized_element.end());
            //json_object_stack_helper->pop();
        }
*/
        std::stack<json_core_t> tmp_stack;
        out = json_core_t::object();
        try{
            while (json_object_stack_helper->size())
            {
                json_core_t &serialized_element = json_object_stack_helper->top();
                tracer.trace(__FUNCTION__, " - merge: ", serialized_element.dump(),
                                   ", to: ", out.dump());
                out.insert(serialized_element.begin(), serialized_element.end());
                tmp_stack.push(std::move(serialized_element));
                json_object_stack_helper->pop();
            }
        }
        catch(...)
        {
            while(tmp_stack.size())
            {
                json_object_stack_helper->push(tmp_stack.top());
                tmp_stack.pop();
            }
            throw;
        }

        while(tmp_stack.size())
        {
            json_object_stack_helper->push(tmp_stack.top());
            tmp_stack.pop();
        }
    }
    else
    {
        tracer.trace(__FUNCTION__, " - nothing to finalize...");
    }

    return out;
}

template<class Tracer>
inline std::string SerializerCore::dump(Tracer tracer) const
{
    auto out = finalize(tracer);
    return out.dump();
}

inline std::shared_ptr<const std::stack<SerializerCore::json_core_t>> SerializerCore::get_shared_mediator_object() const
{
    return json_object_stack_helper;
}

inline std::shared_ptr<std::stack<SerializerCore::json_core_t>> SerializerCore::get_shared_mediator_object()
{
    return json_object_stack_helper;
}
}

#endif // TXML_APPLICATION_JSON_IOCORE_HPP
