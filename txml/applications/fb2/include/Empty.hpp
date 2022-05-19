#ifndef EMPTY_HPP
#define EMPTY_HPP

#include <txml/include/XMLNodeLeaf.hpp>
#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>

#include <txml/applications/fb2/include/fwd/Empty.h>

namespace fb2
{
Empty::Empty(std::string&& str) : base(std::move(str))
{
}

template<class Tracer>
void Empty::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Empty::class_name() << getValue() << " -->\n";
}

template<class Tracer>
std::optional<Empty> Empty::create_impl(/*std::string &name, */txml::TextReaderWrapper &reader, Tracer tracer)
{
    std::optional<Empty> ret;
    if (reader.has_value())
    {
        const std::string& tmp_value = reader.get_value();
        auto it = tmp_value.begin();
        if (*it == '\r' or *it == '\n')
        {
            ++it;
        }
        ret = Empty(std::string(it, tmp_value.end()));
        tracer.trace("Value: '", ret->getValue(), "'");
    }
    return ret;
}
} // namespace fb2
#endif //EMPTY_HPP
