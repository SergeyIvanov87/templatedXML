#ifndef TXML_APPLICATION_JSON_FWD_DESERIALIZER_CORE_H
#define TXML_APPLICATION_JSON_FWD_DESERIALIZER_CORE_H

#include <memory>
#include <stack>

#include <nlohmann/json.hpp>
#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>

namespace json
{
struct DeserializerCore
{
    using json_core_t = nlohmann::json;

    using begin_iterator_t = json_core_t::iterator;
    using end_iterator_t = json_core_t::iterator;
    using range_iterator = std::pair<begin_iterator_t, end_iterator_t>;
    std::stack<range_iterator> iterators_stack;

    DeserializerCore(std::shared_ptr<std::stack<range_iterator>> external_iterators_stack =
       std::shared_ptr<std::stack<range_iterator>>(new std::stack<range_iterator>));

protected:
    ~DeserializerCore();
    std::shared_ptr<std::stack<range_iterator>> json_iterators_stack_helper;
};
}
#endif // TXML_APPLICATION_JSON_FWD_DESERIALIZER_CORE_H
