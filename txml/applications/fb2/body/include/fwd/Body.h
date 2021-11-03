#ifndef FB2_BODY_H
#define FB2_BODY_H

#include <txml/include/fwd/XMLArray.h>

namespace fb2
{
class Section;
class Body : public txml::XMLArray<Body, Section>
{
public:
    using base = txml::XMLArray<Body, Section>;

    static constexpr const char *class_name()
    {
        return "body";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }
};
} // namespace fb2
#endif //FB2_BODY_H
