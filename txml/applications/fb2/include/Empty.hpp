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

const char *Empty::name() const noexcept
{
    return class_name();
}


template<class Tracer>
void Empty::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Empty::class_name() << getValue() << " -->\n";
}

template<class Tracer>
std::shared_ptr<Empty> Empty::create_impl(/*std::string &name, */txml::TextReaderWrapper &reader, Tracer tracer)
{
    std::shared_ptr<Empty> ret;
    if (reader.has_value())
    {
        const std::string& tmp_value = reader.get_value();
        auto it = tmp_value.begin();
        if (*it == '\r' or *it == '\n')
        {
            ++it;
        }
        ret.reset( new Empty(std::string(it, tmp_value.end())));
        tracer.trace("Value: '", ret->getValue(), "'");
    }
    return ret;
}

template<class Formatter, class Tracer>
void Empty::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.template map<Empty>(tracer);
}

template<class Formatter, class Tracer>
std::shared_ptr<Empty> Empty::format_deserialize_impl(Formatter& in, Tracer tracer)
{
    tracer.trace("Begin deserialize map '", class_name(), "'");
    auto ret = in.template map<Empty>(tracer);
    tracer.trace("End deserialize map '", class_name(), "', handle: ", ret.get());
    return ret;
}

template<class Formatter, class Tracer>
void Empty::format_redeserialize_impl(Formatter& in, Tracer tracer)
{
}
} // namespace fb2
#endif //EMPTY_HPP
