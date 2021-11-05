#ifndef UTILS_STDOUT_TRACER_HPP
#define UTILS_STDOUT_TRACER_HPP

#include <iostream>

#include <txml/include/utils/fwd/specific_tracer/StdOutTracer.h>
#include <txml/include/details/TracerPolicies.hpp>
#include <txml/include/utils/Tracer.hpp>

namespace txml
{
template<class ...T>
void StdoutTracer::trace_impl(T&& ...val)
{
    (std::cout << ... << val);
}
} // namespace txml
#endif // UTILS_STDOUT_TRACER_HPP
