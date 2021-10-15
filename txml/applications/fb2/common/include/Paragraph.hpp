#ifndef FB2_PARAGRAPH_HPP
#define FB2_PARAGRAPH_HPP
#include <iostream>
#include <iomanip>
#include <txml/include/XMLCreator.hpp>

#include <txml/applications/fb2/common/include/fwd/Paragraph.h>

#include <txml/applications/fb2/include/FB2TextElement.hpp>

namespace fb2
{
const char *Paragraph::name() const noexcept
{
    return class_name();
}

const Paragraph::value_t &Paragraph::getValue() const
{
    auto val = base::get<FB2TextElement>();
    if (!val)
    {
        std::ostringstream ptr;
        ptr << this;
        std::string ptr_str = ptr.str();
        ptr_str.erase(std::remove_if(ptr_str.begin(), ptr_str.end(), [](char s) {return isspace((int)s);}),
                      ptr_str.end());
        throw std::runtime_error(std::string(Paragraph::class_name()) + " - no value, handle: " +
                                 ptr_str);
    }
    return val->getValue();
}
} // namespace fb2
#endif //FB2_PARAGRAPH_HPP
