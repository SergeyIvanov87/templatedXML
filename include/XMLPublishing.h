#ifndef XDXF_PUBLISHING_H
#define XDXF_PUBLISHING_H

#include <memory>
#include <ostream>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <Framework/Utils/LogTracer.h>


inline std::ostream& no_sep (std::ostream& os);

template<class Value>
struct XMLPublishing
{
    template<class Tracer = Tracer<EmptyTracerImpl>>
    void publish_impl(std::ostream& out, Tracer tracer = Tracer()) const;
};


template<class Value>
struct XMLFormattingPublishing
{
    template<class Formatter, class Tracer = Tracer<EmptyTracerImpl>>
    void format_publish_impl(Formatter& out, Tracer tracer = Tracer()) const;
};
#endif //XDXF_PUBLISHING_H
