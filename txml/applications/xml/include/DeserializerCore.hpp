#ifndef TXML_APPLICATION_XML_DESERIALIZER_CORE_HPP
#define TXML_APPLICATION_XML_DESERIALIZER_CORE_HPP


#include <txml/applications/json/include/fwd/DeserializerCore.h>
#include <txml/include/utils/specific_tracer/EmptyTracer.hpp>

namespace xml
{
inline DeserializerCore::ctor_arg_t DeserializerCore::default_ctor_arg ()
{
    return ctor_arg_t(new DummyArgs);
}

inline DeserializerCore::DeserializerCore(xml_core_t &stream, ctor_arg_t external_helper) :
    in(stream),
    helper(external_helper)
{
}

inline DeserializerCore::~DeserializerCore() = default;

inline std::shared_ptr<const DeserializerCore::DummyArgs> DeserializerCore::get_shared_mediator_object() const
{
    return helper;
}

inline DeserializerCore::ctor_arg_t DeserializerCore::get_shared_mediator_object()
{
    return helper;
}
} // namespace xml
#endif // TXML_APPLICATION_XML_DESERIALIZER_CORE_HPP
