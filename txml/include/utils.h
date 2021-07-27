#ifndef XML_UTILS_H
#define XML_UTILS_H

inline std::string to_string(TextReaderWrapper::NodeType node_type)
{
    switch (node_type)
    {
        case TextReaderWrapper::NodeType::InternalError:
            return "InternalError";
        case TextReaderWrapper::NodeType::None:
            return "None";
        case TextReaderWrapper::NodeType::Element:
            return "Element";
        case TextReaderWrapper::NodeType::Attribute:
            return "Attribute";
        case TextReaderWrapper::NodeType::Text:
            return "Text";
        case TextReaderWrapper::NodeType::CDATA:
            return "CDATA";
        case TextReaderWrapper::NodeType::EntityReference:
            return "EntityReference";
        case TextReaderWrapper::NodeType::Entity:
            return "Entity";
        case TextReaderWrapper::NodeType::ProcessingInstruction:
            return "ProcessingInstruction";
        case TextReaderWrapper::NodeType::Comment:
            return "Comment";
        case TextReaderWrapper::NodeType::Document:
            return "Document";
        case TextReaderWrapper::NodeType::DocumentFragment:
            return "DocumentFragment";
        case TextReaderWrapper::NodeType::Notation:
            return "Notation";
        case TextReaderWrapper::NodeType::Whitespace:
            return "Whitespace";
        case TextReaderWrapper::NodeType::SignificantWhitespace:
            return "SignificantWhitespace";
        case TextReaderWrapper::NodeType::EndElement:
            return "EndElement";
        case TextReaderWrapper::NodeType::EndEntity:
            return "EndEntity";
        case TextReaderWrapper::NodeType::XmlDeclaration:
            return "XmlDeclaration";
        default:
            return "UNSPECIFIED";
    }
    return "UNSPECIFIED";
}

#endif
