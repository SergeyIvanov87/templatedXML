#ifndef TRANSCRIPTION_HPP
#define TRANSCRIPTION_HPP

#include <iostream>

#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>
#include <txml/include/XMLCreator.hpp>

#include <txml/applications/xdxf/include/fwd/Transcription.h>
#include <txml/applications/xdxf/include/TextElement.hpp>

namespace xdxf
{
const char *Transcription::name() const noexcept
{
    return class_name();
}

const Transcription::value_t &Transcription::getValue() const
{
    auto val = base::get<TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(Transcription::class_name()) + " - no value");
    }
    return val->getValue();
}

template<class Formatter, class Tracer>
void Transcription::format_serialize_impl(Formatter& out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.map(*this, tracer);
}

template<class Formatter, class Tracer>
void Transcription::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.template map<Transcription>(tracer);
}

template<class Tracer>
void Transcription::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Transcription::class_name() << ">";
    this->serialize_elements(out, tracer, txml::no_sep);
    out << "</" << Transcription::class_name() << ">\n";
}
} // namespace xdxf
#endif //TRANSCRIPTION_HPP
