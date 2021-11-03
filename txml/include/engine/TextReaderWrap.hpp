#ifndef TXML_ENGINE_TEXT_READER_WRAP_HPP
#define TXML_ENGINE_TEXT_READER_WRAP_HPP

#ifdef WITH_XMLPP
namespace txml
{
using TextReaderWrapper = xmlpp::TextReader;
} // namespace txml
#else
#include <exception>

#include <libxml/xmlreader.h>

namespace txml
{
struct TextReaderWrapper
{
    enum class NodeType
    {
      InternalError = -1,
      None = 0,
      Element = 1,
      Attribute = 2,
      Text = 3,
      CDATA = 4,
      EntityReference = 5,
      Entity = 6,
      ProcessingInstruction = 7,
      Comment = 8,
      Document = 9,
      DocumentType = 10,
      DocumentFragment = 11,
      Notation = 12,
      Whitespace = 13,
      SignificantWhitespace = 14,
      EndElement = 15,
      EndEntity = 16,
      XmlDeclaration = 17
    };

    TextReaderWrapper(const std::string& fileName)
    {
        m_reader = xmlReaderForFile(fileName.c_str(), nullptr, 0);
        if (!m_reader)
        {
            throw std::logic_error("Cannot open file: " + fileName);
        }
    }

    ~TextReaderWrapper()
    {
        xmlFreeTextReader(m_reader);
    }

    bool read()
    {
         return 1 == xmlTextReaderRead(m_reader);
    }

    int get_depth() const
    {
        return xmlTextReaderDepth(m_reader);
    }

    std::string get_name() const
    {
        const char* name = reinterpret_cast<const char*>(xmlTextReaderConstName(m_reader));
        if (name == nullptr)
            name = reinterpret_cast<const char*>(BAD_CAST "--");

        return {name};
    }

    bool has_attributes() const
    {
        return 1 == xmlTextReaderHasAttributes(m_reader);
    }

    bool move_to_first_attribute() {return false;}
    bool move_to_next_attribute() {return false;}
    bool move_to_element() {return false;}

    bool has_value() const
    {
        return 1 == xmlTextReaderHasValue(m_reader);
    }

    std::string get_value() const
    {
        const char* value = reinterpret_cast<const char*>(xmlTextReaderConstValue (m_reader));
        return { value ? value : ""};
    }

    NodeType get_node_type() const
    {
       return static_cast<NodeType>(xmlTextReaderNodeType(m_reader));
    }

    xmlTextReaderPtr m_reader;
};
} // namespace txml
#endif

#endif // TXML_ENGINE_TEXT_READER_WRAP_HPP
