#ifndef XDXF_PUBLISHING_H
#define XDXF_PUBLISHING_H

#include <memory>
#include <ostream>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <utils/Tracer.hpp>


inline std::ostream& no_sep (std::ostream& os);

template<class Value>
struct XMLPublishing
{
    template<class Tracer = EmptyTracer>
    void publish_impl(std::ostream& out, Tracer tracer = Tracer()) const;
};


template<class Value>
struct XMLFormattingPublishing
{
    template<class Formatter, class Tracer = EmptyTracer>
    void format_publish_impl(Formatter& out, Tracer tracer = Tracer()) const;
};
#endif //XDXF_PUBLISHING_H
