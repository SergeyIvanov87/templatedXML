#ifndef UTILS_STDOUT_TRACER_HPP
#define UTILS_STDOUT_TRACER_HPP

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
inline void StdoutTracer::trace_impl(T&& ...val)
{
    (std::cout << ... << print_helper<std::decay_t<T>>()(val));
}

inline void StdoutTracer::dump_impl(std::ostream& out) const
{
    out << "check stdout for traces" << std::endl;
}
} // namespace txml
#endif // UTILS_STDOUT_TRACER_HPP
