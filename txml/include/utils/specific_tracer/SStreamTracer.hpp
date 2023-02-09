#ifndef UTILS_SSTREAM_TRACER_HPP
#define UTILS_SSTREAM_TRACER_HPP

#include <iostream>
#include <limits>
#include <optional>

#include <txml/include/utils/fwd/specific_tracer/StdOutTracer.h>
#include <txml/include/details/TracerPolicies.hpp>
#include <txml/include/utils/Tracer.hpp>
#include <txml/include/engine/fwd/TracerHelper.h>

namespace txml
{
template<class ...T>
inline void SStreamTracer::trace_impl(T&& ...val)
{
    (ss << ... << print_helper<std::decay_t<T>>()(val));
}

inline void SStreamTracer::dump_impl(std::ostream& out) const
{
    out << ss.str() << std::endl;
}
} // namespace txml
#endif // UTILS_SSTREAM_TRACER_HPP
