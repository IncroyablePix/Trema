//
// Created by JajaFil on 4/3/2022.
//

#include <iostream>
#include <algorithm>
#include "StyleApplier.h"
#include "../Utils/StringExtensions.h"
#include "../Activities/Activity.h"

namespace Trema::View
{

    void StyleApplier::ApplyStylesToWindow(const std::unordered_map<std::string, std::shared_ptr<SymbolTable>> &vals,
                                           Activity *activity)
    {
        for(const auto& [elementName, symbolTable] : vals)
        {
            if(elementName == "*") // Global
            {
                SetGlobalStyles(symbolTable, activity);
            }
            else if(elementName[0] == '#') // Id
            {
                auto id = elementName.substr(1);
                auto element = activity->GetElementById<GuiElement>(id);
                SetStyleForElement(element, symbolTable);
            }
        }
    }

    void StyleApplier::SetGlobalStyles(const std::shared_ptr<SymbolTable>& symbolTable, Activity* activity)
    {
        if(!activity)
            return;

        SetStyle(activity->Style, symbolTable);
        activity->ApplyStyle();
    }

    void StyleApplier::SetStyleForElement(const std::shared_ptr<GuiElement>& element, const std::shared_ptr<SymbolTable>& symbolTable)
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
                    style.TextColor().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "text-color-disabled")
            {
                if(type == TYPE_NUM)
                    style.TextDisabledColor().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "widget-background-color")
            {
                if(type == TYPE_NUM)
                    style.WidgetBackgroundColor().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "widget-background-color-hover")
            {
                if(type == TYPE_NUM)
                    style.WidgetBackgroundColorHover().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "widget-background-color-active")
            {
                if(type == TYPE_NUM)
                    style.WidgetBackgroundColorActive().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "button-color")
            {
                if(type == TYPE_NUM)
                    style.ButtonColor().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "button-color-hover")
            {
                if(type == TYPE_NUM)
                    style.ButtonColorHover().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "button-color-active")
            {
                if(type == TYPE_NUM)
                    style.ButtonColorActive().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "menu-background-color")
            {
                if(type == TYPE_NUM)
                    style.MenuBackgroundColor().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "background-color")
            {
                if(type == TYPE_NUM)
                    style.WindowColor().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "header-color")
            {
                if(type == TYPE_NUM)
                    style.HeaderColor().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "header-color-active")
            {
                if(type == TYPE_NUM)
                    style.HeaderActiveColor().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "table-header-color")
            {
                if(type == TYPE_NUM)
                    style.TableHeaderColor().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "popup-background-color")
            {
                if(type == TYPE_NUM)
                    style.PopupBackgroundColor().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "slidergrab-color")
            {
                if(type == TYPE_NUM)
                    style.SliderGrabColor().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "slidergrab-color-active")
            {
                if(type == TYPE_NUM)
                    style.SliderGrabActiveColor().SetColor((int)*value->GetValue().Integer);
            }
            else if(propName == "opacity")
            {
                if(type == TYPE_FLOAT)
                    style.SetAlpha((float)std::clamp<double>(*value->GetValue().Float, 0, 1));
                else if(type == TYPE_STR)
                    style.SetAlpha(value->GetValue().String);
            }
            else if(propName == "orientation")
            {
                if(type == TYPE_STR)
                    style.SetOrientation(value->GetValue().String);
            }
            else if(propName == "window-padding-x")
            {
                if(type == TYPE_FLOAT)
                    style.SetWindowPaddingX((float) *value->GetValue().Float);
                else if(type == TYPE_NUM)
                    style.SetWindowPaddingX((float) *value->GetValue().Integer);
            }
            else if(propName == "window-padding-y")
            {
                if(type == TYPE_FLOAT)
                    style.SetWindowPaddingY((float)*value->GetValue().Float);
                else if(type == TYPE_NUM)
                    style.SetWindowPaddingY((float)*value->GetValue().Integer);
            }
            else if(propName == "window-rounding")
            {
                if(type == TYPE_FLOAT)
                    style.SetWindowRounding((float)*value->GetValue().Float);
                else if(type == TYPE_NUM)
                    style.SetWindowRounding((float)*value->GetValue().Integer);
            }
            else if(propName == "frame-padding-x")
            {
                if(type == TYPE_FLOAT)
                    style.SetFramePaddingX((float) *value->GetValue().Float);
                else if(type == TYPE_NUM)
                    style.SetFramePaddingX((float) *value->GetValue().Integer);
            }
            else if(propName == "frame-padding-y")
            {
                if(type == TYPE_FLOAT)
                    style.SetFramePaddingY((float)*value->GetValue().Float);
                else if(type == TYPE_NUM)
                    style.SetFramePaddingY((float)*value->GetValue().Integer);
            }
            else if(propName == "frame-rounding")
            {
                if(type == TYPE_FLOAT)
                    style.SetFrameRounding((float)*value->GetValue().Float);
                else if(type == TYPE_NUM)
                    style.SetFrameRounding((float)*value->GetValue().Integer);
            }
            else if(propName == "font")
            {
                if(type == TYPE_STR)
                    style.SetFont(value->GetValue().String);
            }
            else if(propName == "header")
            {
                if(type == TYPE_BOOL)
                    style.SetWindowHeaderVisibility(*value->GetValue().Boolean);
            }
            else if(propName == "width")
            {
                if(type == TYPE_STR)
                    style.SetWidth(value->GetValue().String);
            }
            else if(propName == "height")
            {
                if(type == TYPE_STR)
                    style.SetHeight(value->GetValue().String);
            }
            else if(propName == "margin-top")
            {
                if(type == TYPE_STR)
                    style.SetMarginTop(value->GetValue().String);
            }
            else if(propName == "margin-right")
            {
                if(type == TYPE_STR)
                    style.SetMarginRight(value->GetValue().String);
            }
            else if(propName == "margin-bottom")
            {
                if(type == TYPE_STR)
                    style.SetMarginBottom(value->GetValue().String);
            }
            else if(propName == "margin-left")
            {
                if(type == TYPE_STR)
                    style.SetMarginLeft(value->GetValue().String);
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