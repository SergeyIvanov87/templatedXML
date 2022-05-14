#ifndef TXML_APPLICATION_JSON_DESERIALIZER_CORE_HPP
#define TXML_APPLICATION_JSON_DESERIALIZER_CORE_HPP


#include <txml/applications/json/include/fwd/DeserializerCore.h>
#include <txml/include/utils/specific_tracer/EmptyTracer.hpp>

namespace json
{
inline DeserializerCore::ctor_arg_t DeserializerCore::default_ctor_arg ()
{
    return ctor_arg_t(new std::stack<range_iterator>());
}

inline DeserializerCore::DeserializerCore(json_core_t &stream, ctor_arg_t external_iterators_stack) :
    in(stream),
    json_iterators_stack_helper(external_iterators_stack)
{
}

inline DeserializerCore::~DeserializerCore() = default;

inline std::shared_ptr<const std::stack<DeserializerCore::range_iterator>> DeserializerCore::get_shared_mediator_object() const
{
    return json_iterators_stack_helper;
}

inline DeserializerCore::ctor_arg_t DeserializerCore::get_shared_mediator_object()
{
    return json_iterators_stack_helper;
}
} // namespace json
#endif // TXML_APPLICATION_JSON_DESERIALIZER_CORE_HPP
