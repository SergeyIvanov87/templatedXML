#ifndef TXML_APPLICATION_JSON_FWD_SCHEMA_SERIALIZER_H
#define TXML_APPLICATION_JSON_FWD_SCHEMA_SERIALIZER_H

#include <stack>

#include <nlohmann/json.hpp>

#include <txml/include/engine/fwd/SchemaSerializerBase.h>

namespace json
{
template<class Impl, class ...SerializedItems>
struct SchemaToJSON : public txml::SchemaSerializerBase<Impl, txml::StaticCheckUnscopedElement,
                                                  SerializedItems...>
{
    using json = nlohmann::json;
    SchemaToJSON(json &out_obj);
    ~SchemaToJSON();

    // finalize routine: drain all to out
    template<class Tracer>
    void finalize(Tracer tracer);

    // default serialization routine
    template<class SerializedItem, class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<SerializedItem>, Tracer tracer);

    std::string dump() const;
protected:
    json &out;
    std::stack<json> json_object_stack;
    mutable std::string string_result;

    template<class SerializedItem, class Tracer>
    void serialize_schema_tag_impl(const txml::ArrayTag&, Tracer &tracer);
    template<class SerializedItem, class Tracer>
    void serialize_schema_tag_impl(const txml::ContainerTag&, Tracer &tracer);
    template<class SerializedItem, class Tracer>
    void serialize_schema_tag_impl(const txml::LeafTag&, Tracer &tracer);
};
} // namespace json
#endif // TXML_APPLICATION_JSON_FWD_SCHEMA_SERIALIZER_H
