#ifndef TXML_APPLICATION_JSON_FWD_DESERIALIZER_HPP
#define TXML_APPLICATION_JSON_FWD_DESERIALIZER_HPP

#include <txml/applications/json/include/fwd/Deserializer.h>

namespace json
{
#define TEMPL_ARGS_DECL    class Impl, class ...DeserializedItems
#define TEMPL_ARGS_DEF     Impl, DeserializedItems...

template<TEMPL_ARGS_DECL>
FromJSON<TEMPL_ARGS_DEF>::FromJSON(json &obj) :
  in(obj)
{
    iterators_stack.emplace(in.begin(), in.end());
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::shared_ptr<DeserializedItem> FromJSON<TEMPL_ARGS_DEF>::deserialize_impl(txml::details::SchemaDTag<DeserializedItem>, Tracer tracer)
{
    auto& [begin_it, end_it] = iterators_stack.top();
    if (!check_node_param<DeserializedItem>(begin_it, end_it, json::value_t::object, tracer))
    {
        return {};
    }

    iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
    auto ret = create_deserialized_node<DeserializedItem>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
    iterators_stack.pop();
    ++begin_it;

    return ret;
}
#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
}
#endif // TXML_APPLICATION_JSON_FWD_DESERIALIZER_HPP
