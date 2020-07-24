#ifndef XML_UTILS_H
#define XML_UTILS_H

inline std::string to_string(xmlpp::TextReader::NodeType node_type)
{
    switch (node_type)
    {
        case xmlpp::TextReader::NodeType::InternalError:
            return "InternalError";
        case xmlpp::TextReader::NodeType::None:
            return "None";
        case xmlpp::TextReader::NodeType::Element:
            return "Element";
        case xmlpp::TextReader::NodeType::Attribute:
            return "Attribute";
        case xmlpp::TextReader::NodeType::Text:
            return "Text";
        case xmlpp::TextReader::NodeType::CDATA:
            return "CDATA";
        case xmlpp::TextReader::NodeType::EntityReference:
            return "EntityReference";
        case xmlpp::TextReader::NodeType::Entity:
            return "Entity";
        case xmlpp::TextReader::NodeType::ProcessingInstruction:
            return "ProcessingInstruction";
        case xmlpp::TextReader::NodeType::Comment:
            return "Comment";
        case xmlpp::TextReader::NodeType::Document:
            return "Document";
        case xmlpp::TextReader::NodeType::DocumentFragment:
            return "DocumentFragment";
        case xmlpp::TextReader::NodeType::Notation:
            return "Notation";
        case xmlpp::TextReader::NodeType::Whitespace:
            return "Whitespace";
        case xmlpp::TextReader::NodeType::SignificantWhitespace:
            return "SignificantWhitespace";
        case xmlpp::TextReader::NodeType::EndElement:
            return "EndElement";
        case xmlpp::TextReader::NodeType::EndEntity:
            return "EndEntity";
        case xmlpp::TextReader::NodeType::XmlDeclaration:
            return "XmlDeclaration";
        default:
            return "UNSPECIFIED";
    }
    return "UNSPECIFIED";
}

#endif
