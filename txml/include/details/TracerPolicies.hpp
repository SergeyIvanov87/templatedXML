#ifndef TRACER_POLICIES_HPP
#define TRACER_POLICIES_HPP

#include <txml/include/details/fwd/TracerPolicies.h>
#include <txml/include/engine/fwd/TracerHelper.h>

namespace txml
{
template<class T>
struct print_helper
{
    auto operator() (const T &v)
    {
        if constexpr (std::is_base_of_v<txml::TracerHelper<T>, T>)
        {
            return v.hash();
        }
        else
        {
            return v;
        }
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


template<char ident>
void StackedPolicy<ident>::increaseDepth(const StackedPolicy& src)
{
    m_prefix = src.m_prefix;
    m_prefix.push_back(ident_value());
}

template<char ident>
void StackedPolicy<ident>::decreaseDepth()
{
    if(!m_prefix.empty())
    {
        m_prefix.pop_back();
    }
}

template<char ident>
const std::string& StackedPolicy<ident>::getPrefix() const
{
    return m_prefix;
}
} // namespace txml
#endif // TRACER_POLICIES_HPP
