#ifndef TXML_APPLICATION_JSON_DESERIALIZER_CORE_HPP
#define TXML_APPLICATION_JSON_DESERIALIZER_CORE_HPP


#include <txml/applications/json/include/fwd/DeserializerCore.h>
#include <txml/include/utils/specific_tracer/EmptyTracer.hpp>

namespace json
{
inline DeserializerCore::DeserializerCore(std::shared_ptr<std::stack<range_iterator>> external_iterators_stack) :
    json_iterators_stack_helper(external_iterators_stack)
{
}

inline DeserializerCore::~DeserializerCore() = default;
} // namespace json
#endif // TXML_APPLICATION_JSON_DESERIALIZER_CORE_HPP
