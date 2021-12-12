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

inline TextReaderWrapper::TextReaderWrapper(const char *buffer, int size, const char *URL, const char *encoding, int options)
{
    m_reader = xmlReaderForMemory(buffer, size, URL, encoding, options);
    if (!m_reader)
    {
        throw std::logic_error("Cannot open document from memory");
    }
}

inline TextReaderWrapper::TextReaderWrapper(xmlTextReaderPtr existing_reader)
{
    if (!existing_reader)
    {
        throw std::logic_error("Cannot create empty reader");
    }
    m_reader = existing_reader;
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

inline int TextReaderWrapper::get_attributes_count() const
{
    return xmlTextReaderAttributeCount(m_reader);
}

inline bool TextReaderWrapper::move_to_first_attribute()
{
    return 1 == xmlTextReaderMoveToFirstAttribute(m_reader);
}

inline bool TextReaderWrapper::move_to_next_attribute()
{
    return 1 == xmlTextReaderMoveToNextAttribute(m_reader);
}

inline bool TextReaderWrapper::move_to_element()
{
    return 1 == xmlTextReaderMoveToElement(m_reader);
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
