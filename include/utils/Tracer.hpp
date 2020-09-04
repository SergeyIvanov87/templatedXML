#ifndef TRACER
#define TRACER
#include <sstream>
#include <utility>


template<char ident = ' '>
struct StackedPolicy
{
    void increaseDepth()
    {
        m_prefix.push_back(ident_value());
    }

    void decreaseDepth()
    {
        if(m_prefix.empty())
        {
            throw std::logic_error(std::string(__FUNCTION__) + "- prefix is empty");
        }
        m_prefix.pop_back();
    }

    const std::string& getPrefix() const
    {
        return m_prefix;
    }
private:
    std::string m_prefix;
    static constexpr const char ident_value()
    {
        return ident;
    }
};


struct EmptyPolicy
{
    void increaseDepth()
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


template<class Impl, class Policy>
struct TracerBase : Policy
{
    TracerBase() = default;
    TracerBase(TracerBase&&src) = default;
    TracerBase& operator=(TracerBase&&src) = default;

    TracerBase(TracerBase& src)
    {
        Policy::increaseDepth();
    }

    TracerBase& operator=(TracerBase&src)
    {
        Policy::increaseDepth();
        return static_cast<Impl&>(*this);
    }

    ~TracerBase()
    {
        Policy::decreaseDepth();
    }

    template <class T>
    Impl &operator<< (const T &val)
    {
        static_cast<Impl*>(this)->trace(val, Policy::getPrefix());
    }
};

struct StdoutTracer : public TracerBase<StdoutTracer, StackedPolicy<','>>
{
    using BaseType = TracerBase<StdoutTracer, StackedPolicy<','>>;
    using BaseType::operator <<;

    template<class ...T>
    void trace(const T& ...val, std::string prefix = std::string())
    {
        std::cout << prefix << val << ... << std::endl;
    }
};

class EmptyTracer: public TracerBase<EmptyTracer, EmptyPolicy>
{
    using BaseType = TracerBase<EmptyTracer, EmptyPolicy>;
    using BaseType::operator <<;

    template<class ...T>
    void trace(const T& ...val, std::string prefix = std::string())
    {
    }
};

#endif
