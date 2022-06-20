#ifndef FB2_PARAGRAPH_HPP
#define FB2_PARAGRAPH_HPP
#include <iostream>
#include <iomanip>
#include <txml/include/XMLCreator.hpp>

#include <txml/applications/fb2/common/include/fwd/Paragraph.h>

#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
const Paragraph::value_t &Paragraph::value() const
{
    const auto& val = base::node<FB2TextElement>();
    if (!val)
    {
        std::ostringstream ptr;
        ptr << hash();
        std::string ptr_str = ptr.str();
        ptr_str.erase(std::remove_if(ptr_str.begin(), ptr_str.end(), [](char s) {return isspace((int)s);}),
                      ptr_str.end());
        throw std::runtime_error("'" + std::string(Paragraph::class_name()) + "' " + ptr_str + " - no value");
    }
    return val->value();
}
} // namespace fb2
#endif //FB2_PARAGRAPH_HPP
