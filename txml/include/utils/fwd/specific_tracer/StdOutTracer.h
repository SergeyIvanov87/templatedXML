#ifndef UTILS_STDOUT_TRACER_H
#define UTILS_STDOUT_TRACER_H

#include <txml/include/details/fwd/TracerPolicies.h>
#include <txml/include/utils/fwd/Tracer.h>

namespace txml
{
struct StdoutTracer : public TracerBase<StdoutTracer, StackedPolicy<' '>>
{
    using BaseType = TracerBase<StdoutTracer, StackedPolicy<' '>>;
    using BaseType::operator <<;

    template<class ...T>
    void trace_impl(T&& ...val);
};
} // namespace txml
#endif // UTILS_STDOUT_TRACER_H
