#ifndef EMPTY_H
#define EMPTY_H

#include <ostream>
#include <string>

#include <txml/include/fwd/XMLNodeLeaf.h>
#include <txml/include/fwd/XMLSerializable.h>

namespace fb2
{
class Empty : public txml::XMLNodeLeaf<Empty, std::string>,
              public txml::XMLSerializable<Empty>
{
public:
    using base = txml::XMLNodeLeaf<Empty, std::string>;
    using value_t = typename base::value_t;

    static constexpr std::string_view class_name()
    {
        return "!--";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Text;
    };

    Empty(std::string&& str);
    ~Empty() = default;

    template<class Tracer = txml::EmptyTracer>
    static std::optional<Empty> create_impl(/*std::string &name, */txml::TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = txml::EmptyTracer>
    void make_xml_serialize(std::ostream &out, Tracer tracer = Tracer()) const;
};
} // namespace fb2
#endif //EMPTY_H
