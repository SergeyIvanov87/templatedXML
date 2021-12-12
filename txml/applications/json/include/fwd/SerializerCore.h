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
    SerializerCore(std::shared_ptr<std::stack<json_core_t>> external_object_stack =
       std::shared_ptr<std::stack<json_core_t>>(new std::stack<json_core_t>));

    // finalize routine: construct final json_core_t
    template<class Tracer = txml::EmptyTracer>
    json_core_t finalize(Tracer tracer = Tracer()) const;

    template<class Tracer = txml::EmptyTracer>
    std::string dump(Tracer tracer = Tracer()) const;

protected:
    ~SerializerCore();
    std::shared_ptr<std::stack<json_core_t>> json_object_stack_helper;
};
}
#endif // TXML_APPLICATION_JSON_FWD_IOCORE_H
