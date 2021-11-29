#ifndef TXML_APPLICATION_JSON_IOCORE_HPP
#define TXML_APPLICATION_JSON_IOCORE_HPP

#include <txml/applications/json/include/fwd/IOCore.h>
#include <txml/include/utils/specific_tracer/EmptyTracer.hpp>

namespace json
{
IOCore::IOCore(std::shared_ptr<std::stack<json_core_t>> external_object_stack) :
    json_object_stack_helper(external_object_stack)
{
}

IOCore::~IOCore() = default;

template<class Tracer>
IOCore::json_core_t IOCore::finalize(Tracer tracer)
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
        json_object_stack_helper->pop();
    }
    else if (awaiting_element_count > 1)
    {
        tracer.trace(__FUNCTION__, " - from object count: ", awaiting_element_count, ", chose ",
                     utils::json_type_to_cstring(json_core_t::value_t::array), " as result holder");

        out = json_core_t::array();
        for (size_t i = 0; i < json_object_stack_helper->size(); i++)
        {
            json_core_t &serialized_element = json_object_stack_helper->top();
            tracer.trace(__FUNCTION__, " - merge: ", serialized_element.dump(),
                                   ", to: ", out.dump());
            out.insert(out.end(),serialized_element.begin(), serialized_element.end());
            json_object_stack_helper->pop();
        }
    }
    else
    {
        tracer.trace(__FUNCTION__, " - nothing to finalize...");
    }

    return out;
}

template<class Tracer>
std::string IOCore::dump(Tracer tracer) const
{
    auto out = dump(tracer);
    return out.dump();
}
}

#endif // TXML_APPLICATION_JSON_IOCORE_HPP
