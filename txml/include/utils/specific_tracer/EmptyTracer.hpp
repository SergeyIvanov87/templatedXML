#ifndef UTILS_EMPTY_TRACER_HPP
#define UTILS_EMPTY_TRACER_HPP

#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>
#include <txml/include/details/TracerPolicies.hpp>
#include <txml/include/utils/Tracer.hpp>
namespace txml
{
inline void EmptyTracer::dump_impl(std::ostream&) const
{
}
}
#endif // UTILS_EMPTY_TRACER_HPP
