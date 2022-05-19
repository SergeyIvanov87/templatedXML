#ifndef UTILS_STDOUT_TRACER_HPP
#define UTILS_STDOUT_TRACER_HPP

#include <iostream>
#include <limits>
#include <optional>

#include <txml/include/utils/fwd/specific_tracer/StdOutTracer.h>
#include <txml/include/details/TracerPolicies.hpp>
#include <txml/include/utils/Tracer.hpp>

namespace txml
{
template<class T>
struct print_helper
{
    const T& operator() (const T &v)
    {
        return v;
    }
};

template<class T>
struct print_helper<std::optional<T>>
{
    size_t operator() (const std::optional<T> &v)
    {
        return 0;/*
        return v.has_value() ?
               std::hash<T>()(v.value()) :
               std::numeric_limits<size_t>::max();*/
    }
};

template<class ...T>
void StdoutTracer::trace_impl(T&& ...val)
{
    (std::cout << ... << print_helper<std::decay_t<T>>()(val));
}
} // namespace txml
#endif // UTILS_STDOUT_TRACER_HPP
