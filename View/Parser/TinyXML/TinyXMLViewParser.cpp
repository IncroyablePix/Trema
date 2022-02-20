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
#include "../ParsingException.h"

namespace Trema::View
{
    void TinyXMLViewParser::SetupWindowFromFile(const std::string &path, std::shared_ptr<IWindow> window)
    {
        TiXmlDocument doc(path.c_str());
        auto error = doc.LoadFile();
        if(error != TIXML_SUCCESS)
        {
            // TODO : Throw exception
        }
        ParseDocument(doc, window);
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
        ParseElement(pElement, nullptr, window);
    }

    void TinyXMLViewParser::ParseElement(TiXmlElement *element, const std::shared_ptr<IGuiElement>& container, const std::shared_ptr<IWindow>& window)
    {
        auto elementName = element->Value();
        std::unordered_map<std::string, std::string> attributes;
        std::shared_ptr<IGuiElement> newElement;

        for(TiXmlAttribute* attribute = element->FirstAttribute(); attribute != nullptr; attribute = attribute->Next())
            attributes[attribute->Name()] = attribute->Value();

        newElement = CreateFromName(container, elementName, attributes, window);

        //---

        if(container == nullptr)
            TryAddLayout(newElement, window);
        else if(IsLayout(container))
            TryAddToLayout(newElement, container, attributes);
        else
            TryAddAsChild(container, newElement, elementName);

        ParseChildren(element, newElement, window);
    }

    void TinyXMLViewParser::ParseChildren(TiXmlElement *element, const std::shared_ptr<IGuiElement> &container, const std::shared_ptr<IWindow> &window)
    {
        for(TiXmlElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
            ParseElement(child, container, window);
        }
    }
}