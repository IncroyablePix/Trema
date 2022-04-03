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
                SetGlobalStyles(symbolTable);
            }
            else if(elementName[0] == '#') // Id
            {
                auto id = elementName.substr(1);
                auto element = window->GetElementById<IGuiElement>(id);
                SetStyleForElement(element, symbolTable);
            }
        }
    }

    void StyleApplier::SetGlobalStyles(const std::shared_ptr<SymbolTable>& symbolTable)
    {
        /*for(const auto& [propName, value] : *symbolTable)
        {
            std::cout << "\t[" << propName << ":" << *value << "]\n";
        }
        std::cout << std::endl;*/
    }

    void StyleApplier::SetStyleForElement(const std::shared_ptr<IGuiElement>& element, std::shared_ptr<SymbolTable> symbolTable)
    {
        if(!element)
            return;

        for(const auto& [propName, value] : *symbolTable)
        {
            auto type = value->GetType();

            if(propName == "text-color")
            {
                if(type == TYPE_NUM)
                    element->Style.SetTextColor((int)(value->GetPtrValue<int64_t>()));
                else if(type == TYPE_STR)
                    element->Style.SetTextColor(value->GetValue<char*>());
            }
            else if(propName == "opacity")
            {
                if(type == TYPE_FLOAT)
                    element->Style.SetAlpha((float)std::clamp<double>((value->GetPtrValue<double>()), 0, 1));
                else if(type == TYPE_STR)
                    element->Style.SetAlpha(value->GetValue<char*>());
            }

            /*std::cout << "\t[" << propName << ":" << *value;
            if(type == TYPE_NUM)
                std::cout << "(" << ToHex(*((int64_t*)value->GetValue())) << ")";

            std::cout << "]\n";*/
        }
        //std::cout << std::endl;
    }
}