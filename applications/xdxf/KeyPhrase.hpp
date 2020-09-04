#ifndef KEY_PHRASE_HPP
#define KEY_PHRASE_HPP
#include <iostream>

#include "xdxf/KeyPhrase.h"
#include "xdxf/TextElement.hpp"
#include "XMLProducible.hpp"
#include "XMLPublishing.hpp"
#include "XMLCreator.hpp"

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
bool KeyPhrase::initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, depth, reader, tracer);
    return true;
}


template<class Tracer>
void KeyPhrase::dump(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << KeyPhrase::class_name() << ">";
    this->dump_all(out, tracer, no_sep);
    out << "</" << KeyPhrase::class_name() << ">\n";
}

template<class Formatter, class Tracer = EmptyTracer>
void KeyPhrase::format_dump(Formatter& out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.map(*this, tracer);
}
#endif //KEY_PHRASE_HPP
