#ifndef SERIALIZER_DISPATCHER_H
#define SERIALIZER_DISPATCHER_H

#include <txml/include/engine/fwd/DispatcherBase.h>

namespace txml
{
template <class ...Contexts>
struct SerializerDispatcher : public DispatcherBase<Contexts...>
{
    using base_t = DispatcherBase<Contexts...>;
    using base_t::dispatch_context;

    template<class ...Args>
    SerializerDispatcher(Args &&...args) :
        base_t(std::forward<Args>(args)...)
    {
    }

    template<class InElement, class Tracer>
    void map(const InElement& in_val, Tracer tracer) {
        auto* element_processing_context = this->template dispatch_context<InElement>();
        if constexpr (not std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template map<InElement>(in_val, tracer);
        }
    }

    template<class SerializedItem, class Tracer>
    void serialize_impl(const SerializedItem& value, Tracer tracer)
    {
        auto* element_processing_context = this->template dispatch_context<SerializedItem>();
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_impl(value, tracer);
        }
    }

    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::ArrayTag &t, Tracer &tracer)
    {
        auto* element_processing_context = this->template dispatch_context<SerializedItem>();
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_tag_impl<SerializedItem>(value, t, tracer);
        }
    }

    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::ContainerTag &t, Tracer &tracer)
    {
        auto* element_processing_context = this->template dispatch_context<SerializedItem>();
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_tag_impl<SerializedItem>(value, t, tracer);
        }
    }

    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::LeafTag &t, Tracer &tracer)
    {
        auto* element_processing_context = this->template dispatch_context<SerializedItem>();
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_tag_impl<SerializedItem>(value, t, tracer);
        }
    }

    //TODO why not templated tag???
    template<class SerializedItem, class Tracer>
    void serialize_tag_impl(const SerializedItem& value, const txml::NoDataTag &t, Tracer &tracer)
    {
        auto* element_processing_context = this->template dispatch_context<SerializedItem>();
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            element_processing_context->template serialize_tag_impl<SerializedItem>(value, t, tracer);
        }
    }
};
} // namespace txml
#endif // SERIALIZER_DISPATCHER_H
