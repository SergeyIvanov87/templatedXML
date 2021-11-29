#ifndef TXML_APPLICATION_JSON_FWD_SCHEMA_SERIALIZER_H
#define TXML_APPLICATION_JSON_FWD_SCHEMA_SERIALIZER_H

#include <txml/include/engine/fwd/SchemaSerializerBase.h>
#include <txml/applications/json/include/fwd/IOCore.h>

namespace json
{
template<class Impl, class ...SerializedItems>
struct SchemaToJSON : public virtual IOCore,
                      public txml::SchemaSerializerBase<Impl, txml::StaticCheckUnscopedElement,
                                                  SerializedItems...>
{
    using json = nlohmann::json;
    SchemaToJSON(std::shared_ptr<std::stack<json>> shared_object_stack =
                                 std::shared_ptr<std::stack<json>>(new std::stack<json>));
    ~SchemaToJSON();

    // default serialization routine
    template<class SerializedItem, class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<SerializedItem>, Tracer tracer);

protected:

    template<class SerializedItem, class Tracer>
    void serialize_schema_tag_impl(const txml::ArrayTag&, Tracer &tracer);
    template<class SerializedItem, class Tracer>
    void serialize_schema_tag_impl(const txml::ContainerTag&, Tracer &tracer);
    template<class SerializedItem, class Tracer>
    void serialize_schema_tag_impl(const txml::LeafTag&, Tracer &tracer);
};
} // namespace json
#endif // TXML_APPLICATION_JSON_FWD_SCHEMA_SERIALIZER_H
