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

template<class T>//, class = std::enable_if_t<std::is_base_of<txml::XMLProducible<T>, T>::value, int>>
struct print_helper<std::optional<T>>
{
    std::string operator() (const std::optional<T> &v)
    {
        return v.has_value() ?
               v.value().hash() :
               "has_no_value";
    }
};

template<class ...T>
void StdoutTracer::trace_impl(T&& ...val)
{
    (std::cout << ... << print_helper<std::decay_t<T>>()(val));
}
} // namespace txml
#endif // UTILS_STDOUT_TRACER_HPP
