#ifndef UTILS_STREAM_TRACER_H
#define UTILS_STREAM_TRACER_H

#include <sstream>
#include <txml/include/details/fwd/TracerPolicies.h>
#include <txml/include/utils/fwd/Tracer.h>

namespace txml
{
struct SStreamTracer : public TracerBase<SStreamTracer, StackedPolicy<' '>>
{
    using BaseType = TracerBase<SStreamTracer, StackedPolicy<' '>>;
    using BaseType::operator <<;

    template<class ...T>
    void trace_impl(T&& ...val);

    void dump_impl(std::ostream& out) const;
private:
    std::stringstream ss;
};
} // namespace txml
#endif // UTILS_STREAM_TRACER_H
