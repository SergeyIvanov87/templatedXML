#ifndef UTILS_EMPTY_TRACER_H
#define UTILS_EMPTY_TRACER_H

#include <txml/include/details/fwd/TracerPolicies.h>
#include <txml/include/utils/fwd/Tracer.h>

namespace txml
{
struct EmptyTracer: public TracerBase<EmptyTracer, EmptyPolicy>
{
    using BaseType = TracerBase<EmptyTracer, EmptyPolicy>;
    using BaseType::operator <<;

    template<class ...T>
    void trace_impl(T&& ...val)
    {
    }
};
} // namespace txml
#endif // UTILS_EMPTY_TRACER_H
