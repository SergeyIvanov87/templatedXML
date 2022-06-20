#ifndef TXML_APPLICATION_JSON_FWD_SCHEMA_SERIALIZER_H
#define TXML_APPLICATION_JSON_FWD_SCHEMA_SERIALIZER_H

#include <txml/include/engine/fwd/SchemaSerializerBase.h>
#include <txml/applications/json/include/fwd/SerializerCore.h>

namespace json
{
template<class Impl, class ...SerializedItems>
struct SchemaToJSON : public virtual SerializerCore,
                      public txml::SchemaSerializerBase<Impl, txml::StaticCheckUnscopedElement,
                                                  SerializedItems...>
{
    using core_t = SerializerCore;
    using json_core_t = core_t::json_core_t;
    using ctor_arg_t = core_t::ctor_arg_t;

    static constexpr std::string_view class_name() { return Impl::name(); }

    SchemaToJSON(ctor_arg_t shared_object_stack = core_t::default_ctor_arg());
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
    template<class SerializedItem, class Tracer>
    void serialize_schema_tag_impl(const txml::NoDataTag&, Tracer &tracer);
private:
    static constexpr std::string_view name() { return "SchemaToJSON"; }
};
} // namespace json
#endif // TXML_APPLICATION_JSON_FWD_SCHEMA_SERIALIZER_H
