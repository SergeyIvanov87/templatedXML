#ifndef TXML_APPLICATION_JSON_SERIALIZER_HPP
#define TXML_APPLICATION_JSON_SERIALIZER_HPP

#include <txml/include/engine/FormatSerializerBase.hpp>
#include <txml/applications/json/include/fwd/Serializer.h>
#include <txml/applications/json/include/utils.hpp>

namespace json
{
#define TEMPL_ARGS_DECL    class Impl, class ...SerializedItems
#define TEMPL_ARGS_DEF     Impl, SerializedItems...

template<TEMPL_ARGS_DECL>
ToJSON<TEMPL_ARGS_DEF>::ToJSON(json &out_obj) :
  out(out_obj)
{
    iterators_stack.emplace(out.begin(), out.end());
}


template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void ToJSON<TEMPL_ARGS_DEF>::serialize_impl(const SerializedItem &val, Tracer tracer)
{
    serialize_tag_impl(val, typename SerializedItem::tags_t {}, tracer);
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void ToJSON<TEMPL_ARGS_DEF>::serialize_tag_impl(const SerializedItem& value, const txml::ArrayTag&, Tracer &tracer)
{
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void ToJSON<TEMPL_ARGS_DEF>::serialize_tag_impl(const SerializedItem& value, const txml::ContainerTag&, Tracer &tracer)
{
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void ToJSON<TEMPL_ARGS_DEF>::serialize_tag_impl(const SerializedItem& value, const txml::LeafTag&, Tracer &tracer)
{
}
} // namespace json
#endif // TXML_APPLICATION_JSON_SERIALIZER_HPP
