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
                    style.TextColor().SetColor((int)(value->GetPtrValue<int64_t>()));
            }
            else if(propName == "text-color-disabled")
            {
                if(type == TYPE_NUM)
                    style.TextDisabledColor().SetColor((int)(value->GetPtrValue<int64_t>()));
            }
            else if(propName == "widget-background-color")
            {
                if(type == TYPE_NUM)
                    style.WidgetBackgroundColor().SetColor((int) (value->GetPtrValue<int64_t>()));
            }
            else if(propName == "menu-background-color")
            {
                if(type == TYPE_NUM)
                    style.MenuBackgroundColor().SetColor((int)(value->GetPtrValue<int64_t>()));
            }
            else if(propName == "background-color")
            {
                if(type == TYPE_NUM)
                    style.WindowColor().SetColor((int)(value->GetPtrValue<int64_t>()));
            }
            else if(propName == "header-color")
            {
                if(type == TYPE_NUM)
                    style.HeaderColor().SetColor((int)(value->GetPtrValue<int64_t>()));
            }
            else if(propName == "header-color-active")
            {
                if(type == TYPE_NUM)
                    style.HeaderActiveColor().SetColor((int)(value->GetPtrValue<int64_t>()));
            }
            else if(propName == "table-header-color")
            {
                if(type == TYPE_NUM)
                    style.TableHeaderColor().SetColor((int)(value->GetPtrValue<int64_t>()));
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
            else if(propName == "window-padding-x")
            {
                if(type == TYPE_FLOAT)
                    style.SetWindowPaddingX((float) value->GetPtrValue<double>());
                else if(type == TYPE_NUM)
                    style.SetWindowPaddingX((float) value->GetPtrValue<int64_t>());
            }
            else if(propName == "window-padding-y")
            {
                if(type == TYPE_FLOAT)
                    style.SetWindowPaddingY((float)value->GetPtrValue<double>());
                else if(type == TYPE_NUM)
                    style.SetWindowPaddingY((float)value->GetPtrValue<int64_t>());
            }
            else if(propName == "window-rounding")
            {
                if(type == TYPE_FLOAT)
                    style.SetWindowRounding((float)value->GetPtrValue<double>());
                else if(type == TYPE_NUM)
                    style.SetWindowRounding((float)value->GetPtrValue<int64_t>());
            }
            else if(propName == "frame-padding-x")
            {
                if(type == TYPE_FLOAT)
                    style.SetFramePaddingX((float) value->GetPtrValue<double>());
                else if(type == TYPE_NUM)
                    style.SetFramePaddingX((float) value->GetPtrValue<int64_t>());
            }
            else if(propName == "frame-padding-y")
            {
                if(type == TYPE_FLOAT)
                    style.SetFramePaddingY((float)value->GetPtrValue<double>());
                else if(type == TYPE_NUM)
                    style.SetFramePaddingY((float)value->GetPtrValue<int64_t>());
            }
            else if(propName == "frame-rounding")
            {
                if(type == TYPE_FLOAT)
                    style.SetFrameRounding((float)value->GetPtrValue<double>());
                else if(type == TYPE_NUM)
                    style.SetFrameRounding((float)value->GetPtrValue<int64_t>());
            }
            else if(propName == "font")
            {
                if(type == TYPE_STR)
                    style.SetFont(value->GetValue<char*>());
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