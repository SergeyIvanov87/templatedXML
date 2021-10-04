#ifndef FB2_BINARY_HPP
#define FB2_BINARY_HPP
#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>
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
    this->serialize_elements(out, tracer, txml::no_sep);
    out << "</" << Binary::class_name() << ">\n";
}

template<class Formatter, class Tracer>
void Binary::format_deserialize_impl(Formatter& in, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    in.template map<Binary>(tracer);
}

template<class Formatter, class Tracer>
void Binary::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.template map<Binary>(tracer);
}
} // namespace fb2
#endif //FB2_BINARY_HPP
