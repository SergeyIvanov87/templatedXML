#ifndef SERIALIZER_DISPATCHER_H
#define SERIALIZER_DISPATCHER_H

#include <txml/include/engine/fwd/DispatcherBase.h>

namespace txml
{
template <class VirtualBaseContext, class ...Contexts>
struct SerializerVirtualDispatcher : public DispatcherVirtualBase<VirtualBaseContext, Contexts...>
{
    using base_t = DispatcherVirtualBase<VirtualBaseContext, Contexts...>;
    using base_t::dispatch_context;

    template<class ...Args>
    SerializerVirtualDispatcher(Args &&...args) :
        VirtualBaseContext(std::forward<Args>(args)...),
        base_t(std::forward<Args>(args)...)
    {
    }

    template<class InElement, class Tracer>
    void map(const InElement& in_val, Tracer tracer) {
        tracer.trace("from dispatcher mapping");
        auto* element_processing_context = this->template dispatch_context<InElement>(tracer);
        if constexpr (not std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template map<InElement>(in_val, tracer);
        }
    }

    template<class SerializedItem, class Tracer>
    void serialize_impl(const SerializedItem& value, Tracer tracer)
    {
        tracer.trace("from dispatcher serialize_impl");
        auto* element_processing_context = this->template dispatch_context<SerializedItem>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_impl(value, tracer);
        }
    }

    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::ArrayTag &t, Tracer &tracer)
    {
        tracer.trace("from dispatcher `ArrayTag`");
        auto* element_processing_context = this->template dispatch_context<SerializedItem>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_tag_impl<SerializedItem>(value, t, tracer);
        }
    }

    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::ContainerTag &t, Tracer &tracer)
    {
        tracer.trace("from dispatcher `ContainerTag`");
        auto* element_processing_context = this->template dispatch_context<SerializedItem>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_tag_impl<SerializedItem>(value, t, tracer);
        }
    }

    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::LeafTag &t, Tracer &tracer)
    {
        tracer.trace("from dispatcher `LeafTag`");
        auto* element_processing_context = this->template dispatch_context<SerializedItem>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_tag_impl<SerializedItem>(value, t, tracer);
        }
    }

    //TODO why not templated tag???
    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::NoDataTag &t, Tracer &tracer)
    {
        tracer.trace("from dispatcher `NoDataTag`");
        auto* element_processing_context = this->template dispatch_context<SerializedItem>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_tag_impl<SerializedItem>(value, t, tracer);
        }
    }
};
} // namespace txml
#endif // SERIALIZER_DISPATCHER_H
