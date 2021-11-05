#ifndef TXML_ENGINE_TEXT_READER_WRAP_HPP
#define TXML_ENGINE_TEXT_READER_WRAP_HPP

#include <txml/include/engine/fwd/TextReaderWrap.h>

#ifndef WITH_XMLPP

namespace txml
{
inline TextReaderWrapper::TextReaderWrapper(const std::string& fileName)
{
    m_reader = xmlReaderForFile(fileName.c_str(), nullptr, 0);
    if (!m_reader)
    {
        throw std::logic_error("Cannot open file: " + fileName);
    }
}

inline TextReaderWrapper::~TextReaderWrapper()
{
    xmlFreeTextReader(m_reader);
}

inline bool TextReaderWrapper::read()
{
    return 1 == xmlTextReaderRead(m_reader);
}

inline int TextReaderWrapper::get_depth() const
{
    return xmlTextReaderDepth(m_reader);
}

inline std::string TextReaderWrapper::get_name() const
{
    const char* name = reinterpret_cast<const char*>(xmlTextReaderConstName(m_reader));
    if (name == nullptr)
        name = reinterpret_cast<const char*>(BAD_CAST "--");

    return {name};
}

inline bool TextReaderWrapper::has_attributes() const
{
    return 1 == xmlTextReaderHasAttributes(m_reader);
}

inline bool TextReaderWrapper::has_value() const
{
    return 1 == xmlTextReaderHasValue(m_reader);
}

inline std::string TextReaderWrapper::get_value() const
{
    const char* value = reinterpret_cast<const char*>(xmlTextReaderConstValue (m_reader));
    return { value ? value : ""};
}

inline TextReaderWrapper::NodeType TextReaderWrapper::get_node_type() const
{
    return static_cast<NodeType>(xmlTextReaderNodeType(m_reader));
}
} // namespace txml
#endif

#endif // TXML_ENGINE_TEXT_READER_WRAP_HPP
