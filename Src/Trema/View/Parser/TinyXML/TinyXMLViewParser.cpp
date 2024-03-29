#include <iostream>
#include <utility>
#include "TinyXMLViewParser.h"
#include "../../Exceptions/ParsingException.h"
#include "../../Components/Widgets/Options/Radio.h"
#include "../MissingAttributeException.h"
#include "../../Style/MistakesContainer.h"

namespace Trema::View
{
    TinyXMLViewParser::TinyXMLViewParser(std::unique_ptr<IStyleParser> styleParser, MistakesContainer& mistakes) :
            ViewParser(std::move(styleParser), mistakes)
    {

    }

    void TinyXMLViewParser::LoadView(const std::string &path, std::shared_ptr<Window> window, Activity& activity)
    {
        TiXmlDocument doc(path.c_str());
        auto error = doc.LoadFile();
        if(error != TIXML_SUCCESS)
        {

        }

        ParseDocument(doc, window, activity);
        ApplyStyles(window, activity);
    }

    void TinyXMLViewParser::SetupWindowFromString(const std::string &code, std::shared_ptr<Window> window, Activity& activity)
    {
        std::stringstream stream(code);
        TiXmlDocument doc;
        doc.Parse(stream.str().c_str());

        ParseDocument(doc, window, activity);
        ApplyStyles(window, activity);
    }

    void TinyXMLViewParser::ParseDocument(TiXmlDocument &document, std::shared_ptr<Window> window, Activity& activity)
    {
        TiXmlElement* pElement;
        //---

        pElement = document.RootElement();

        if(pElement->Value() != std::string("App"))
        {
            std::stringstream ss;
            ss << "Root element should be of type \"App\". Found: [" << pElement->Value() <<  "]";
            throw ParsingException(ss.str().c_str());
        }

        ParseRoots(pElement, window, activity);
    }

    void TinyXMLViewParser::ParseRoots(TiXmlElement *element, std::shared_ptr<Window> window, Activity& activity)
    {
        for (TiXmlElement *child = element->FirstChildElement();
             child != nullptr; child = child->NextSiblingElement())
        {
            auto val = child->Value();
            if(val == std::string("Head"))
            {
                ParseHead(child, window, activity);
            }
            else if(val == std::string("Body"))
            {
                ParseBody(child, window, activity);
            }
        }
    }

    void TinyXMLViewParser::ParseHead(TiXmlElement *head, std::shared_ptr<Window> window, Activity& activity)
    {
        for (TiXmlElement *child = head->FirstChildElement();
             child != nullptr; child = child->NextSiblingElement())
        {
            std::unordered_map<std::string, std::string> attributes;

            for(TiXmlAttribute* attribute = child->FirstAttribute(); attribute != nullptr; attribute = attribute->Next())
                attributes[attribute->Name()] = attribute->Value();

            auto elementName = child->Value();
            auto innerText = child->GetText();
            HeadElementFromName(elementName, std::string(innerText ? innerText : ""), attributes, window, activity);
        }
    }

    void TinyXMLViewParser::ParseBody(TiXmlElement *body, std::shared_ptr<Window> window, Activity& activity)
    {
        auto* child = body->FirstChildElement();
        ParseElement(child, nullptr, window, activity);
    }

    void TinyXMLViewParser::ParseElement(TiXmlElement *element, const std::shared_ptr<GuiElement>& container, std::shared_ptr<Window> window, Activity& activity)
    {
        auto elementName = element->Value();
        auto elementContent = element->GetText();
        std::unordered_map<std::string, std::string> attributes;
        std::shared_ptr<GuiElement> newElement;

        for(TiXmlAttribute* attribute = element->FirstAttribute(); attribute != nullptr; attribute = attribute->Next())
            attributes[attribute->Name()] = attribute->Value();

        newElement = CreateFromName(container, elementName, attributes, window, activity, elementContent ? elementContent : std::string(""));

        //---
        if(!newElement)
        {
            m_mistakes << CompilationMistake { .Line = static_cast<unsigned int>(element->Row()), .Position = static_cast<unsigned int>(element->Column()), .Code = ErrorCode::ElementNotFound, .Extra = elementName };
            return;
        }

        ParseChildren(element, newElement, window, activity);

        try
        {
            if (container == nullptr)
                TryAddLayout(newElement, activity); // Try add as layout
            else if (IsType<Layout>(container))
                TryAddToLayout(newElement, container, attributes, activity); // Add container to layout
            else if (IsType<TopMenu>(newElement))
                TryAddTopMenu(newElement, activity);
            else
                TryAddAsChild(container, newElement, elementName); // Add to container
        }
        catch(const ParsingException &e)
        {
            m_mistakes << CompilationMistake { .Line = static_cast<unsigned int>(element->Row()), .Position = static_cast<unsigned int>(element->Column()), .Code = ErrorCode::MisplacedElement, .Extra = e.what() };
        }
        catch(const MissingAttributeException &e)
        {
            m_mistakes << CompilationMistake { .Line = static_cast<unsigned int>(element->Row()), .Position = static_cast<unsigned int>(element->Column()), .Code = ErrorCode::MissingAttribute, .Extra = e.what() };
        }
    }

    void TinyXMLViewParser::ParseChildren(TiXmlElement *element, const std::shared_ptr<GuiElement> &container, std::shared_ptr<Window> window, Activity& activity)
    {
        for (TiXmlElement *child = element->FirstChildElement();
             child != nullptr; child = child->NextSiblingElement())
        {
            ParseElement(child, container, window, activity);
        }
    }
}