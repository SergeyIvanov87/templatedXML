#ifndef EMPTY_H
#define EMPTY_H

#include <ostream>
#include <string>

#include <txml/include/fwd/XMLNodeLeaf.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

namespace fb2
{
class Empty : public txml::XMLNodeLeaf<Empty, std::string>,
              public txml::XMLSerializable<Empty>,
              public txml::XMLFormatDeserializable<Empty>,
              public txml::XMLSchemaSerializable<Empty>
{
public:
    using base = txml::XMLNodeLeaf<Empty, std::string>;
    using value_t = typename base::value_t;

    static constexpr const char* class_name()
    {
        return "!--";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Text;
    };

    Empty(std::string&& str);
    ~Empty() = default;

    const char *name() const noexcept override;

    template<class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Empty> create_impl(/*std::string &name, */txml::TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = txml::EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Empty> format_deserialize_impl(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_redeserialize_impl(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_impl(Formatter& out, Tracer tracer = Tracer());
};
} // namespace fb2
#endif //EMPTY_H
