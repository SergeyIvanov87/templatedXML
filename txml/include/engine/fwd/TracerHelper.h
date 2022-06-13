#ifndef TRACER_HELPER_H
#define TRACER_HELPER_H

#include <string>

namespace txml
{
template<class Node>
struct TracerHelper
{
    TracerHelper() = default;
    TracerHelper(const TracerHelper&) = default;
    TracerHelper(TracerHelper&&) = default;
    TracerHelper& operator=(const TracerHelper&) = default;
    TracerHelper& operator=(TracerHelper&&) = default;
    std::string hash() const noexcept;
private:
    mutable std::string hash_value;
};
} // namespace txml
#endif // TRACER_HELPER_H
