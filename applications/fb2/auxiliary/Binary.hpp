#ifndef FB2_BINARY_HPP
#define FB2_BINARY_HPP
#include <iostream>

#include "common/fb2/auxiliary/Binary.h"
#include "common/fb2/Empty.hpp"
#include "common/xml/XMLProducible.hpp"
#include "common/xml/XMLPublishing.hpp"
#include "common/xml/XMLCreator.hpp"

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
bool Binary::initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, depth, reader, tracer);
    return true;
}


template<class Tracer>
void Binary::dump(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Binary::class_name() << ">";
    this->dump_all(out, tracer, no_sep);
    out << "</" << Binary::class_name() << ">\n";
}

#endif //FB2_BINARY_HPP
