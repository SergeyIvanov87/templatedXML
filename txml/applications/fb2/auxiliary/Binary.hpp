#ifndef FB2_BINARY_HPP
#define FB2_BINARY_HPP
#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/auxiliary/Binary.h>
#include <txml/applications/fb2/Empty.hpp>

const char *Binary::name() const noexcept
{
    return class_name();
}

const Binary::value_t &Binary::getValue() const
{
    auto val = base::get<Empty>();
    if (!val)
    {
        throw std::runtime_error(std::string(Binary::class_name()) + " - no value");
    }
    return val->getValue();
}

template<class Tracer>
void Binary::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Binary::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << Binary::class_name() << ">\n";
}

#endif //FB2_BINARY_HPP
