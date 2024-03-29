#ifndef SERIALIZER_SCHEMA_DISPATCHER_H
#define SERIALIZER_SCHEMA_DISPATCHER_H

#include <txml/include/engine/fwd/DispatcherBase.h>

namespace txml
{
template <class VirtualBaseContext, class ...Contexts>
struct SerializerSchemaDispatcher : public DispatcherVirtualBase<VirtualBaseContext, Contexts...>
{
    using base_t = DispatcherVirtualBase<VirtualBaseContext, Contexts...>;
    using base_t::dispatch_context;

    template<class ...Args>
    SerializerSchemaDispatcher(Args &&...args) :
        VirtualBaseContext(std::forward<Args>(args)...),
        base_t(std::forward<Args>(args)...)
    {
    }

    template<class InElement, class Tracer>
    void map(Tracer tracer) {
        auto* element_processing_context = this->template dispatch_context<InElement>(tracer);
        if constexpr (not std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template map<InElement>(tracer);
        }
    }

    template<class InElement, class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<InElement>, Tracer tracer)
    {
        auto* element_processing_context = this->template dispatch_context<InElement>(tracer);
        //element_processing_context->template serialize_schema_tag_impl<InElement>(typename InElement::tags_t {}, tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_schema_impl(txml::details::SchemaTag<InElement> {} , tracer);
        }
    }

    template<class InElement, class Tracer>
    void serialize_schema_tag_impl(const txml::ArrayTag&, Tracer &tracer)
    {
        auto* element_processing_context = this->template dispatch_context<InElement>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_schema_tag_impl<InElement>(txml::ArrayTag{} , tracer);
        }
    }

    template<class InElement, class Tracer>
    void serialize_schema_tag_impl(const txml::ContainerTag&, Tracer &tracer)
    {
        auto* element_processing_context = this->template dispatch_context<InElement>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_schema_tag_impl<InElement>(txml::ContainerTag{} , tracer);
        }
    }

    template<class InElement, class Tracer>
    void serialize_schema_tag_impl(const txml::LeafTag&, Tracer &tracer)
    {
        auto* element_processing_context = this->template dispatch_context<InElement>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_schema_tag_impl<InElement>(txml::LeafTag{} , tracer);
        }
    }

    template<class InElement, class Tracer>
    void serialize_schema_tag_impl(const txml::NoDataTag&, Tracer &tracer)
    {
        auto* element_processing_context = this->template dispatch_context<InElement>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_schema_tag_impl<InElement>(txml::NoDataTag{} , tracer);
        }
    }
};
} // namespace txml
#endif // SERIALIZER_SCHEMA_DISPATCHER_H
