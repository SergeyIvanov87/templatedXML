#ifndef EMPTY_H
#define EMPTY_H

#include <ostream>

#include <txml/include/fwd/XMLNodeLeaf.h>
#include <txml/include/fwd/XMLSerializable.h>

class Empty : public XMLNodeLeaf<std::string>,
                public XMLSerializable<Empty>
{
public:
    using base = XMLNodeLeaf<std::string>;
    using value_t = typename base::value_t;

    static constexpr const char* class_name()
    {
        return "!--";
    }

    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return TextReaderWrapper::NodeType::Text;
    };

    Empty(std::string&& str);
    ~Empty() = default;

    const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    static std::shared_ptr<Empty> create_impl(std::string &name, TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};

#endif //EMPTY_H
