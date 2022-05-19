#ifndef FB2_TEXT_ELEMENT_H
#define FB2_TEXT_ELEMENT_H

#include <ostream>
#include <regex>
#include <string>

#include <txml/include/fwd/XMLNodeLeaf.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

namespace fb2
{
class FB2TextElement : public txml::XMLNodeLeaf<FB2TextElement, std::string>,
                       public txml::XMLSerializable<FB2TextElement>
{
public:
    using base = txml::XMLNodeLeaf<FB2TextElement, std::string>;
    using value_t = typename base::value_t;

    static constexpr std::string_view class_name()
    {
        return "#text";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Text;
    };

    FB2TextElement(std::string&& str);
    ~FB2TextElement() = default;

    template<class Tracer = txml::EmptyTracer>
    static std::optional<FB2TextElement> create_impl(/*std::string &name, */txml::TextReaderWrapper &reader, Tracer tracer);

/*    template<class Tracer = txml::EmptyTracer>
    void fill_impl(std::string &name, txml::TextReaderWrapper &reader, Tracer tracer);
*/
    template<class Tracer = txml::EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};
} // namespace fb2
#endif //KEY_PHRASE_H
