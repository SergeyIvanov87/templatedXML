#ifndef DESERIALIZER_DISPATCHER_H
#define DESERIALIZER_DISPATCHER_H

#include <txml/include/engine/fwd/DispatcherBase.h>

namespace txml
{
template <class ...Contexts>
struct DeserializerDispatcher : public DispatcherBase<Contexts...>
{
    using base_t = DispatcherBase<Contexts...>;
    using base_t::dispatch_context;

    template<class ...Args>
    DeserializerDispatcher(Args &&...args) :
        base_t(std::forward<Args>(args)...)
    {
    }

    template<class InElement, class Tracer>
    std::shared_ptr<InElement> map(Tracer tracer) {
        auto* element_processing_context = this->template dispatch_context<InElement>(tracer);
        if constexpr (not std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            return element_processing_context->template map<InElement>(tracer);
        }
        else
        {
            // TODO use Policy?
            return {};
        }
    }

    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_impl(txml::details::SchemaDTag<DeserializedItem>, Tracer tracer)
    {
        auto* element_processing_context = this->template dispatch_context<DeserializedItem>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            return element_processing_context->template deserialize_impl(txml::details::SchemaDTag<DeserializedItem> {} , tracer);
        }
        else
        {
            // TODO use Policy?
            return {};
        }
    }

    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::ArrayTag&, Tracer &tracer)
    {
        auto* element_processing_context = this->template dispatch_context<DeserializedItem>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            return element_processing_context->template deserialize_tag_impl<DeserializedItem>(txml::ArrayTag{} , tracer);
        }
        else
        {
            // TODO use Policy?
            return {};
        }
    }

    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::ContainerTag&, Tracer &tracer)
    {
        auto* element_processing_context = this->template dispatch_context<DeserializedItem>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            return element_processing_context->template deserialize_tag_impl<DeserializedItem>(txml::ContainerTag{} , tracer);
        }
        else
        {
            // TODO use Policy?
            return {};
        }
    }

    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::LeafTag&, Tracer &tracer)
    {
        auto* element_processing_context = this->template dispatch_context<DeserializedItem>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            return element_processing_context->template deserialize_tag_impl<DeserializedItem>(txml::LeafTag{} , tracer);
        }
        else
        {
            // TODO use Policy?
            return {};
        }
    }

    //TODO why not templated tag???
    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::NoDataTag&, Tracer &tracer)
    {
        auto* element_processing_context = this->template dispatch_context<DeserializedItem>(tracer);
        if constexpr (!std::is_same_v<typename std::remove_pointer<decltype(element_processing_context)>::type, details::EmptyContext>)
        {
            return element_processing_context->template deserialize_tag_impl<DeserializedItem>(txml::NoDataTag{} , tracer);
        }
        else
        {
            // TODO use Policy?
            return {};
        }
    }
};
} // namespace txml
#endif // DESERIALIZER_DISPATCHER_H
