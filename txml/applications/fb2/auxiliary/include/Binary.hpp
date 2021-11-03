#ifndef FB2_BINARY_HPP
#define FB2_BINARY_HPP
#include <iostream>

#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/auxiliary/include/fwd/Binary.h>
#include <txml/applications/fb2/include/Empty.hpp>

namespace fb2
{
const char *Binary::name() const noexcept
{
    return class_name();
}

const Binary::value_t &Binary::getValue() const
{
    auto val = base::getValue<Empty>();
    if (!val)
    {
        throw std::runtime_error(std::string(Binary::class_name()) + " - no value");
    }
    return val->getValue();
}
} // namespace fb2
#endif //FB2_BINARY_HPP
