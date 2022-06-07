#ifndef TXML_ENGINE_TRACER_HELPER_HPP
#define TXML_ENGINE_TRACER_HELPER_HPP

#include <txml/include/engine/fwd/TracerHelper.h>

namespace txml
{
template<class Node>
std::string TracerHelper<Node>::hash() const noexcept
{
    // lazy initialization happens on tracer clame only
    static thread_local size_t counter = 0;
    if (hash_value.empty())
    {
        hash_value = std::string(Node::class_name()) + std::to_string(++counter);
    }
    return hash_value;
}
}

#endif // TXML_ENGINE_TRACER_HELPER_HPP
