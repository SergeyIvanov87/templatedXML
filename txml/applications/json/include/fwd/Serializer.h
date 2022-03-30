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
    using json = nlohmann::json;
    using core_t = SerializerCore;

    ToJSON(std::shared_ptr<std::stack<json>> shared_object_stack =
                           std::shared_ptr<std::stack<json>>(new std::stack<json>));

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
};
} // namespace json
#endif // TXML_APPLICATION_JSON_FWD_SERIALIZER_H
