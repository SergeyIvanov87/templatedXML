#ifndef XDXF_CREATABLE_H
#define XDXF_CREATABLE_H

#include <memory>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <utils/Tracer.hpp>

template<class Value>
struct XMLProducible
{
    template<class Tracer = EmptyTracer>
    static std::shared_ptr<Value> create_impl(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer);

    template<class Tracer = EmptyTracer>
    void fill_impl(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer);
};

#endif //XDXF_CREATABLE_H
