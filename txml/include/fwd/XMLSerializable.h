#ifndef XDXF_PUBLISHING_H
#define XDXF_PUBLISHING_H

#include <memory>
#include <ostream>

#include <txml/include/utils/Tracer.hpp>

namespace txml
{
inline std::ostream& no_sep (std::ostream& os);

template<class Value>
struct XMLSerializable
{
    template<class Tracer = txml::EmptyTracer>
    void serialize(std::ostream& out, Tracer tracer = Tracer()) const;
};


template<class Value>
struct XMLFormatSerializable
{
    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_serialize(Formatter& out, Tracer tracer = Tracer()) const;
};

template<class Value>
struct XMLSchemaSerializable
{
    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize(Formatter& out, Tracer tracer = Tracer());
};
} // namespace txml
#endif //XDXF_PUBLISHING_H
