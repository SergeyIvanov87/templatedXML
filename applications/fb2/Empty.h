#ifndef EMPTY_H
#define EMPTY_H

#include <ostream>

#include "common/xml/XMLNodeLeaf.h"
#include "common/xml/XMLPublishing.h"

class Empty : public XMLNodeLeaf<std::string>,
                public XMLPublishing<Empty>
{
public:
    using base = XMLNodeLeaf<std::string>;
    using value_t = typename base::value_t;

    static constexpr const char* class_name()
    {
        return "!--";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Text;
    };

    Empty(std::string&& str);
    ~Empty() = default;

    const char *name() const noexcept override;

    template<class Tracer = Tracer<EmptyTracerImpl>>
    static std::shared_ptr<Empty> create_impl(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer);

    template<class Tracer = Tracer<EmptyTracerImpl>>
    void dump(std::ostream &out, Tracer tracer = Tracer()) const;
};

#endif //EMPTY_H
