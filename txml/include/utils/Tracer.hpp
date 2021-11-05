#ifndef UTILS_TRACER_HPP
#define UTILS_TRACER_HPP

#include <txml/include/utils/fwd/Tracer.h>

namespace txml
{

#define TEMPL_ARGS_DECL    class Impl, class Policy
#define TEMPL_ARGS_DEF     Impl, Policy

template<TEMPL_ARGS_DECL>
TracerBase<TEMPL_ARGS_DEF>::TracerBase(TracerBase& src)
{
    Policy::increaseDepth(src);
}

template<TEMPL_ARGS_DECL>
TracerBase<TEMPL_ARGS_DEF>& TracerBase<TEMPL_ARGS_DEF>::operator=(TracerBase&src)
{
    Policy::increaseDepth(src);
    return static_cast<Impl&>(*this);
}

template<TEMPL_ARGS_DECL>
TracerBase<TEMPL_ARGS_DEF>::~TracerBase()
{
    Policy::decreaseDepth();
}

template<TEMPL_ARGS_DECL>
Impl &TracerBase<TEMPL_ARGS_DEF>::self() noexcept
{
    return const_cast<Impl&>(static_cast<const self_t*>(this)->self());
}

template<TEMPL_ARGS_DECL>
const Impl &TracerBase<TEMPL_ARGS_DEF>::self() const noexcept
{
    return *static_cast<const Impl*>(this);
}

template<TEMPL_ARGS_DECL>
Impl &TracerBase<TEMPL_ARGS_DEF>::operator<<(std::ios_base& (*func)(std::ios_base&))
{
    self().trace_impl(func);
    return self();
}

template<TEMPL_ARGS_DECL>
Impl &TracerBase<TEMPL_ARGS_DEF>::operator<< (std::ostream& (*func)( std::ostream& ) )
{
    self().trace_impl(func);
    return self();
}

#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif // UTILS_TRACER_HPP
