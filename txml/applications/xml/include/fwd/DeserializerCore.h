#ifndef TXML_APPLICATION_XML_FWD_DESERIALIZER_CORE_H
#define TXML_APPLICATION_XML_FWD_DESERIALIZER_CORE_H

#include <memory>

#include <txml/include/engine/TextReaderWrap.hpp>
#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>

namespace xml
{
struct DeserializerCore
{
    using xml_core_t = txml::TextReaderWrapper;
    struct DummyArgs {};
    using ctor_arg_t = std::shared_ptr<DummyArgs>;
    static ctor_arg_t default_ctor_arg ();

    DeserializerCore(xml_core_t &stream, ctor_arg_t external_helper = default_ctor_arg());

    std::shared_ptr<const DummyArgs> get_shared_mediator_object() const;
    ctor_arg_t get_shared_mediator_object();
protected:
    ~DeserializerCore();
    xml_core_t &in;
    ctor_arg_t helper;
};
} // namespace xml
#endif // TXML_APPLICATION_XML_FWD_DESERIALIZER_CORE_H
