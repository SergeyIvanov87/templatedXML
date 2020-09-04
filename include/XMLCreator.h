#ifndef XDXF_CREATOR_H
#define XDXF_CREATOR_H

#include <memory>
#include <string>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <utils/Tracer.hpp>

struct XMLCreator
{
    template<class Value, class Tracer = EmptyTracer>
    static std::shared_ptr<Value> try_create(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer = Tracer());

    template<class Value, class Tracer = EmptyTracer>
    static std::shared_ptr<Value> try_fill(std::shared_ptr<Value> to_fill, std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer = Tracer());
};

#endif //XDXF_CREATOR_H
