#ifndef TRACER_POLICIES_HPP
#define TRACER_POLICIES_HPP

#include <txml/include/details/fwd/TracerPolicies.h>

namespace txml
{
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
