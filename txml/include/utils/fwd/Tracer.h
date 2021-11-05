#ifndef UTILS_TRACER_H
#define UTILS_TRACER_H
#include <sstream>
#include <utility>

namespace txml
{
template<class Impl, class Policy>
struct TracerBase : Policy
{
    TracerBase() = default;
    TracerBase(TracerBase&&src) = default;
    TracerBase& operator=(TracerBase&&src) = default;

    using self_t = TracerBase<Impl, Policy>;

    TracerBase(TracerBase& src);
    TracerBase& operator=(TracerBase&src);
    ~TracerBase();

    Impl& self() noexcept;
    const Impl& self() const noexcept;

    template <class T>
    Impl &operator<< (const T &val)
    {
        self().trace_impl(Policy::getPrefix(), val);
        return self();
    }

    Impl& operator<<(
    std::ios_base& (*func)(std::ios_base&));

    Impl &operator<< (
    std::ostream& (*func)( std::ostream& ) );

    template<class ...T>
    void trace(const T& ...val)
    {
        self().trace_impl(Policy::getPrefix(), val...);
        *this << std::endl;
    }
};
} // namespace txml
#endif // UTILS_TRACER_H
