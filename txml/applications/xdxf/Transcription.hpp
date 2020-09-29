#ifndef TRANSCRIPTION_HPP
#define TRANSCRIPTION_HPP
#include <iostream>

#include "xdxf/Transcription.h"
#include "xdxf/TextElement.hpp"
#include "XMLSerializable.h"
#include "XMLCreator.hpp"
#

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

template<class Formatter, class Tracer = EmptyTracer>
void Transcription::format_serialize_impl(Formatter& out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.map(*this, tracer);
}

template<class Tracer>
void Transcription::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Transcription::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << Transcription::class_name() << ">\n";
}

#endif //TRANSCRIPTION_HPP
