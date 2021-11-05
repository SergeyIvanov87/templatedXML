#ifndef TXML_APPLICATION_JSON_FWD_SERIALIZER_H
#define TXML_APPLICATION_JSON_FWD_SERIALIZER_H

#include <stack>

#include <nlohmann/json.hpp>

#include <txml/include/engine/fwd/FormatSerializerBase.h>

namespace json
{
template<class Impl, class ...SerializedItems>
struct ToJSON : public txml::FormatSerializerBase<Impl, txml::StaticCheckUnscopedElement,
                                                  SerializedItems...>
{
    using json = nlohmann::json;
    ToJSON(json &out_obj);

    // default serialization routine
    template<class SerializedItem, class Tracer>
    void serialize_impl(const SerializedItem& value, Tracer tracer);

protected:
    json &out;

    using begin_iterator_t = json::iterator;
    using end_iterator_t = json::iterator;
    using range_iterator = std::pair<begin_iterator_t, end_iterator_t>;
    std::stack<range_iterator> iterators_stack;

    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::ArrayTag&, Tracer &tracer);
    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::ContainerTag&, Tracer &tracer);
    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::LeafTag&, Tracer &tracer);
};
} // namespace json
#endif // TXML_APPLICATION_JSON_FWD_SERIALIZER_H
