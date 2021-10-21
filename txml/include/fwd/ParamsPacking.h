#ifndef PARAMS_PACKING_H
#define PARAMS_PACKING_H

#include <txml/include/utils/Tracer.hpp>

namespace txml
{
template <class T = EmptyTracer>
struct ParamsPacket {
    template <class ...Args> class Params {
        using Tracer = T;
    public:
        Params(Args &&...args, Tracer tracer = Tracer()) :
            m_tracer(std::move(tracer)),
            m_params(std::forward<Args>(args)...)
        {
        }

        Tracer &get_tracer()
        {
            return m_tracer;
        }

        template<class Arg>
        Arg& get()
        {
            return std::get<Arg>(m_params);
        }
    private:
        Tracer m_tracer;
        std::tuple<Args...> m_params;
    };
};

template<class ...Args>
using DefaultParamsPacket = ParamsPacket<>::Params<Args...>;
} // namespace txml
#endif // PARAMS_PACKING_H
