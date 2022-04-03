//
// Created by JajaFil on 2/18/2022.
//

#include <iostream>
#include <utility>
#include <SDL2/SDL_log.h>
#include <sstream>
#include "TinyXMLViewParser.h"
#include "tinyxml.h"
#include "../../Components/Container/IContainer.h"
#include "../../Exceptions/ParsingException.h"
#include "../../Components/Widgets/Options/Radio.h"

namespace Trema::View
{
    TinyXMLViewParser::TinyXMLViewParser(std::unique_ptr<IStyleParser> styleParser) :
            IViewParser(std::move(styleParser))
    {

    }

    void TinyXMLViewParser::SetupWindowFromFile(const std::string &path, std::shared_ptr<IWindow> window)
    {
        TiXmlDocument doc(path.c_str());
        auto error = doc.LoadFile();
        if(error != TIXML_SUCCESS)
        {
            // TODO : Throw exception
        }
        ParseDocument(doc, window);
        ApplyStyles(window);
    }

    void TinyXMLViewParser::SetupWindowFromFile(const std::wstring &path, std::shared_ptr<IWindow> window)
    {
        // TiXmlDocument doc(path.c_str());
        // doc.LoadFile();
        // ParseDocument(doc, window);
    }

    void TinyXMLViewParser::SetupWindowFromString(const std::string &code, std::shared_ptr<IWindow> window)
    {

    }

    void TinyXMLViewParser::ParseDocument(TiXmlDocument &document, std::shared_ptr<IWindow> window)
    {
        TiXmlHandle hDoc(&document);
        TiXmlElement* pElement;
        //---

        pElement = document.RootElement();

        if(pElement->Value() != std::string("App"))
        {
            std::stringstream ss;
            ss << "Root element should be of type \"App\". Found: [" << pElement->Value() <<  "]";
            throw ParsingException(ss.str().c_str());
        }

        ParseRoots(pElement, window);
    }

    void TinyXMLViewParser::ParseRoots(TiXmlElement *element, const std::shared_ptr<IWindow> &window)
    {
        for (TiXmlElement *child = element->FirstChildElement();
             child != nullptr; child = child->NextSiblingElement())
        {
            auto val = child->Value();
            if(val == std::string("Head"))
            {
                ParseHead(child, window);
            }
            else if(val == std::string("Body"))
            {
                ParseBody(child, window);
            }
        }
    }

    void TinyXMLViewParser::ParseHead(TiXmlElement *head, const std::shared_ptr<IWindow> &window)
    {
        for (TiXmlElement *child = head->FirstChildElement();
             child != nullptr; child = child->NextSiblingElement())
        {
            std::unordered_map<std::string, std::string> attributes;

            for(TiXmlAttribute* attribute = child->FirstAttribute(); attribute != nullptr; attribute = attribute->Next())
                attributes[attribute->Name()] = attribute->Value();

            auto elementName = child->Value();
            auto innerText = child->GetText();
            HeadElementFromName(elementName, std::string(innerText ? innerText : ""), attributes, window);
        }
    }

    void TinyXMLViewParser::ParseBody(TiXmlElement *body, const std::shared_ptr<IWindow> &window)
    {
        auto* child = body->FirstChildElement();
        ParseElement(child, nullptr, window);
    }

    void TinyXMLViewParser::ParseElement(TiXmlElement *element, const std::shared_ptr<IGuiElement>& container, const std::shared_ptr<IWindow>& window)
    {
        auto elementName = element->Value();
        auto elementContent = element->GetText();
        std::unordered_map<std::string, std::string> attributes;
        std::shared_ptr<IGuiElement> newElement;

        for(TiXmlAttribute* attribute = element->FirstAttribute(); attribute != nullptr; attribute = attribute->Next())
            attributes[attribute->Name()] = attribute->Value();

        newElement = CreateFromName(container, elementName, attributes, window, elementContent ? elementContent : std::string(""));

        //---

        ParseChildren(element, newElement, window);
        if(container == nullptr)
            TryAddLayout(newElement, window); // Try add as layout
        else if(IsType<ILayout>(container))
            TryAddToLayout(newElement, container, attributes, window); // Add container to layout
        else if(IsType<TopMenu>(newElement))
            TryAddTopMenu(newElement, window);
        else
            TryAddAsChild(container, newElement, elementName); // Add to container
    }

    void TinyXMLViewParser::ParseChildren(TiXmlElement *element, const std::shared_ptr<IGuiElement> &container, const std::shared_ptr<IWindow> &window)
    {
        for (TiXmlElement *child = element->FirstChildElement();
             child != nullptr; child = child->NextSiblingElement())
        {
            ParseElement(child, container, window);
        }
    }
}