#ifndef FB2_SECTION_H
#define FB2_SECTION_H

#include <txml/include/fwd/XMLArray.h>

namespace fb2
{
class Paragraph;
class Section : public txml::XMLArray<Section, Paragraph>
{
public:
    using base = txml::XMLArray<Section, Paragraph>;

    static constexpr std::string_view class_name()
    {
        return "section";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }
};
} // namespace fb2
#endif //FB2_SECTION_H
