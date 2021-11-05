#ifndef TRACER_POLICIES_H
#define TRACER_POLICIES_H

#include <string>

namespace txml
{
template<char ident = ' '>
struct StackedPolicy
{
    void increaseDepth(const StackedPolicy& src);
    void decreaseDepth();
    const std::string& getPrefix() const;

private:
    std::string m_prefix;
    static constexpr const char ident_value()
    {
        return ident;
    }
};


struct EmptyPolicy
{
    void increaseDepth(const EmptyPolicy&src)
    {
    }

    void decreaseDepth()
    {
    }

    const std::string& getPrefix() const
    {
        static const std::string empty;
        return empty;
    }
};

} // namespace txml

#endif // TRACER_POLICIES_H
