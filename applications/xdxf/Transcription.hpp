#ifndef TRANSCRIPTION_HPP
#define TRANSCRIPTION_HPP
#include <iostream>

#include "common/xdxf/Transcription.h"
#include "common/xdxf/TextElement.hpp"
#include "common/xml/XMLProducible.hpp"
#include "common/xml/XMLPublishing.h"
#include "common/xml/XMLCreator.hpp"
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

template<class Formatter, class Tracer = Tracer<EmptyTracerImpl>>
void Transcription::format_dump(Formatter& out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.map(*this, tracer);
}

template<class Tracer>
void Transcription::dump(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Transcription::class_name() << ">";
    this->dump_all(out, tracer, no_sep);
    out << "</" << Transcription::class_name() << ">\n";
}

template<class Tracer>
bool Transcription::initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, depth, reader, tracer);
    return true;
}
#endif //TRANSCRIPTION_HPP
