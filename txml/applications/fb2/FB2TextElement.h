#ifndef FB2_TEXT_ELEMENT_H
#define FB2_TEXT_ELEMENT_H

#include <ostream>
#include <regex>

#include "XMLNodeLeaf.h"
#include "XMLSerializable.h"

class FB2TextElement : public XMLNodeLeaf<std::string>,
                       public XMLSerializable<FB2TextElement>
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

    template<class Tracer = EmptyTracer>
    static std::shared_ptr<FB2TextElement> create_impl(std::string &name, xmlpp::TextReader &reader, Tracer tracer);

/*    template<class Tracer = EmptyTracer>
    void fill_impl(std::string &name, xmlpp::TextReader &reader, Tracer tracer);
*/
    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};

#endif //KEY_PHRASE_H
