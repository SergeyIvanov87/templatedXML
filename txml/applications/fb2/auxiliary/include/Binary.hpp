#ifndef FB2_BINARY_HPP
#define FB2_BINARY_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/auxiliary/include/fwd/Binary.h>
#include <txml/applications/fb2/include/Empty.hpp>

namespace fb2
{
inline const Binary::value_t &Binary::value() const
{
    const auto& val = base::node<Empty>();
    if (!val)
    {
        throw std::runtime_error(std::string(Binary::class_name()) + " - no value");
    }
    return val->value();
}
} // namespace fb2
#endif //FB2_BINARY_HPP
