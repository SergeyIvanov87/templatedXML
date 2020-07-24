#ifndef FB2_TEXT_ELEMENT_H
#define FB2_TEXT_ELEMENT_H

#include <ostream>


#include "common/xml/XMLNodeLeaf.h"
#include "common/xml/XMLPublishing.h"

class FB2TextElement : public XMLNodeLeaf<std::string>,
                       public XMLPublishing<FB2TextElement>
{
public:
    using base = XMLNodeLeaf<std::string>;
    using value_t = typename base::value_t;

    static constexpr const char* class_name()
    {
        return "#text";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Text;
    };

    FB2TextElement(std::string&& str);
    ~FB2TextElement() = default;

    const char *name() const noexcept override;

    template<class Tracer = Tracer<EmptyTracerImpl>>
    static std::shared_ptr<FB2TextElement> create_impl(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer);

/*    template<class Tracer = Tracer<EmptyTracerImpl>>
    void fill_impl(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer);
*/
    template<class Tracer = Tracer<EmptyTracerImpl>>
    void dump(std::ostream &out, Tracer tracer = Tracer()) const;
};

#endif //KEY_PHRASE_H
