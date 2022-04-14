//
// Created by JajaFil on 4/3/2022.
//

#include <iostream>
#include <algorithm>
#include "StyleApplier.h"
#include "../Utils/StringExtensions.h"

namespace Trema::View
{

    void StyleApplier::ApplyStylesToWindow(const std::unordered_map<std::string, std::shared_ptr<SymbolTable>> &vals,
                                           const std::shared_ptr<IWindow>& window)
    {
        for(const auto& [elementName, symbolTable] : vals)
        {
            if(elementName == "*") // Global
            {
                SetGlobalStyles(symbolTable, window);
            }
            else if(elementName[0] == '#') // Id
            {
                auto id = elementName.substr(1);
                auto element = window->GetElementById<IGuiElement>(id);
                SetStyleForElement(element, symbolTable);
            }
        }

        if(window)
            window->ApplyStyle();
    }

    void StyleApplier::SetGlobalStyles(const std::shared_ptr<SymbolTable>& symbolTable, const std::shared_ptr<IWindow> &window)
    {
        if(!window)
            return;

        SetStyle(window->Style, symbolTable);
        window->ApplyStyle();
    }

    void StyleApplier::SetStyleForElement(const std::shared_ptr<IGuiElement>& element, const std::shared_ptr<SymbolTable>& symbolTable)
    {
        if(!element) // TODO: Throw exception ?
            return;

        SetStyle(element->Style, symbolTable);
    }

    void StyleApplier::SetStyle(ElementStyle& style, const std::shared_ptr<SymbolTable>& symbolTable)
    {
        for(const auto& [propName, value] : *symbolTable)
        {
            auto type = value->GetType();

            if(propName == "text-color")
            {
                if(type == TYPE_NUM)
                    style.SetTextColor((int)(value->GetPtrValue<int64_t>()));
            }
            else if(propName == "background-color")
            {
                if(type == TYPE_NUM)
                    style.SetBackgroundColor((int)(value->GetPtrValue<int64_t>()));
            }
            else if(propName == "header-color")
            {
                if(type == TYPE_NUM)
                    style.SetHeaderColor((int)(value->GetPtrValue<int64_t>()));
            }
            else if(propName == "opacity")
            {
                if(type == TYPE_FLOAT)
                    style.SetAlpha((float)std::clamp<double>((value->GetPtrValue<double>()), 0, 1));
                else if(type == TYPE_STR)
                    style.SetAlpha(value->GetValue<char*>());
            }
            else if(propName == "orientation")
            {
                if(type == TYPE_STR)
                    style.SetOrientation(value->GetValue<char*>());
            }
            else if(propName == "padding-x")
            {
                if(type == TYPE_FLOAT)
                    style.SetPaddingX((float)value->GetPtrValue<double>());
                else if(type == TYPE_NUM)
                    style.SetPaddingX((float)value->GetPtrValue<int64_t>());
            }
            else if(propName == "padding-y")
            {
                if(type == TYPE_FLOAT)
                    style.SetPaddingY((float)value->GetPtrValue<double>());
                else if(type == TYPE_NUM)
                    style.SetPaddingY((float)value->GetPtrValue<int64_t>());
            }
            else if(propName == "rounding")
            {
                if(type == TYPE_FLOAT)
                    style.SetRounding((float)value->GetPtrValue<double>());
                else if(type == TYPE_NUM)
                    style.SetRounding((float)value->GetPtrValue<int64_t>());
            }
            else if(propName == "font")
            {
                if(type == TYPE_STR)
                    style.SetFont(CopyStr(value->GetValue<char*>()));
            }

            /*std::cout << "\t[" << propName << ":" << *value;
            if(type == TYPE_NUM)
                std::cout << "(" << ToHex(*((int64_t*)value->GetValue())) << ")";

            std::cout << "]\n";*/
        }
        //std::cout << std::endl;
    }

    char *StyleApplier::CopyStr(const char* str)
    {
        if(!str)
            return nullptr;

        auto copied = new char[strlen(str)];
        strcpy(copied, str);

        return copied;
    }
}