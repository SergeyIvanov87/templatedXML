#ifndef TRACER_HELPER_H
#define TRACER_HELPER_H

#include <string>

namespace txml
{
template<class Node>
struct TracerHelper
{
    std::string hash() const noexcept;
private:
    mutable std::string hash_value;
};
} // namespace txml
#endif // TRACER_HELPER_H
