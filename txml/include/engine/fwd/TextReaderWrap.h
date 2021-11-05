#ifndef TXML_ENGINE_TEXT_READER_WRAP_H
#define TXML_ENGINE_TEXT_READER_WRAP_H

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

    TextReaderWrapper(const std::string& fileName);
    ~TextReaderWrapper();

    bool read();
    int get_depth() const;
    std::string get_name() const;
    bool has_attributes() const;

    bool move_to_first_attribute() {return false;}
    bool move_to_next_attribute() {return false;}
    bool move_to_element() {return false;}

    bool has_value() const;
    std::string get_value() const;
    NodeType get_node_type() const;

    xmlTextReaderPtr m_reader;
};
} // namespace txml
#endif

#endif // TXML_ENGINE_TEXT_READER_WRAP_H
