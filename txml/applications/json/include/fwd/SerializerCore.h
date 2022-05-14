#ifndef TXML_APPLICATION_JSON_FWD_IOCORE_H
#define TXML_APPLICATION_JSON_FWD_IOCORE_H

#include <memory>
#include <stack>
#include <string>

#include <nlohmann/json.hpp>
#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>

namespace json
{
struct SerializerCore
{
    using json_core_t = nlohmann::json;
    using ctor_arg_t = std::shared_ptr<std::stack<json_core_t>>;
    static ctor_arg_t default_ctor_arg ();
    SerializerCore(ctor_arg_t external_object_stack = default_ctor_arg());

    // finalize routine: construct final json_core_t
    template<class Tracer = txml::EmptyTracer>
    json_core_t finalize(Tracer tracer = Tracer()) const;

    template<class Tracer = txml::EmptyTracer>
    void finalize(json_core_t &out, Tracer tracer = Tracer()) const;


    template<class Tracer = txml::EmptyTracer>
    std::string dump(Tracer tracer = Tracer()) const;

    std::shared_ptr<const std::stack<json_core_t>> get_shared_mediator_object() const;
    ctor_arg_t get_shared_mediator_object();
protected:
    ~SerializerCore();
    ctor_arg_t json_object_stack_helper;
};
}
#endif // TXML_APPLICATION_JSON_FWD_IOCORE_H
