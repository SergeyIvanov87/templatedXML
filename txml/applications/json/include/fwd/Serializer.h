#ifndef TXML_APPLICATION_JSON_FWD_SERIALIZER_H
#define TXML_APPLICATION_JSON_FWD_SERIALIZER_H

#include <stack>

#include <nlohmann/json.hpp>

#include <txml/include/engine/fwd/FormatSerializerBase.h>
#include <txml/applications/json/include/fwd/SerializerCore.h>

namespace json
{
template<class Impl, class ...SerializedItems>
struct ToJSON : public virtual SerializerCore,
                public txml::FormatSerializerBase<Impl, txml::StaticCheckUnscopedElement,
                                                  SerializedItems...>
{
    using core_t = SerializerCore;
    using json_core_t = core_t::json_core_t;
    using ctor_arg_t = core_t::ctor_arg_t;

    static constexpr std::string_view class_name() { return Impl::name(); }

    ToJSON(ctor_arg_t shared_object_stack = core_t::default_ctor_arg());

    // default serialization routine
    template<class SerializedItem, class Tracer>
    void serialize_impl(const SerializedItem& value, Tracer tracer);

protected:
    ~ToJSON();

    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::ArrayTag&, Tracer &tracer);
    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::ContainerTag&, Tracer &tracer);
    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::LeafTag&, Tracer &tracer);
    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::NoDataTag&, Tracer &tracer);
private:
    static constexpr std::string_view name() { return "ToJSON"; }
};
} // namespace json
#endif // TXML_APPLICATION_JSON_FWD_SERIALIZER_H
