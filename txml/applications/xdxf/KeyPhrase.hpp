#ifndef KEY_PHRASE_HPP
#define KEY_PHRASE_HPP
#include <iostream>

#include "xdxf/KeyPhrase.h"
#include "xdxf/TextElement.hpp"
#include "XMLSerializable.hpp"

const char *KeyPhrase::name() const noexcept
{
    return class_name();
}

const KeyPhrase::value_t &KeyPhrase::getValue() const
{
    auto val = base::get<TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(KeyPhrase::class_name()) + " - no value");
    }
    return val->getValue();
}


template<class Tracer>
void KeyPhrase::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << KeyPhrase::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << KeyPhrase::class_name() << ">\n";
}

template<class Formatter, class Tracer = EmptyTracer>
void KeyPhrase::format_serialize_impl(Formatter& out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.map(*this, tracer);
}
#endif //KEY_PHRASE_HPP
