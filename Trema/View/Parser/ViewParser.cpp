//
// Created by JajaFil on 2/18/2022.
//

#include <sstream>
#include <iterator>
#include <utility>
#include <vector>
#include <iostream>
#include "ViewParser.h"
#include "../Components/Container/WindowContainer.h"
#include "../Components/Widgets/Options/Radio.h"
#include "../Components/Widgets/Options/Combo.h"
#include "../Components/Widgets/Button.h"
#include "../Components/Widgets/Pure/Text.h"
#include "../Components/Widgets/Checkbox.h"
#include "../Components/Widgets/DataContainers/Table.h"
#include "../Components/Widgets/Input/TextInput.h"
#include "../Components/Widgets/Input/TextArea.h"
#include "../Exceptions/ParsingException.h"
#include "../Components/Widgets/Options/SelectorOption.h"
#include "../Utils/StringExtensions.h"
#include "../Components/TopMenu/SubMenu.h"
#include "../Components/TopMenu/MenuOption.h"
#include "../Components/Widgets/Pure/Separator.h"
#include "../Components/Layout/Docking/MainDockSpace.h"
#include "../Components/Layout/StackSpace/StackSpace.h"
#include "../Components/Layout/LayoutException.h"
#include "../Style/StyleApplier.h"
#include "../Components/Widgets/Sliders/SliderFloat.h"
#include "../Components/Widgets/ColorPicker.h"
#include "../Components/Widgets/Sliders/SliderInt.h"

namespace Trema::View
{
    ViewParser::ViewParser(std::unique_ptr<IStyleParser> stylesParser) :
        m_stylesParser(std::move(stylesParser))
    {

    }

    void ViewParser::ApplyStyles(const std::shared_ptr<Window>& window)
    {
        auto vals = m_stylesParser->GetVariables();
        StyleApplier applier;

        applier.ApplyStylesToWindow(vals, window);
    }

    void ViewParser::HeadElementFromName(const std::string& elementName, const std::string& content, std::unordered_map<std::string, std::string>& attributes, std::shared_ptr<Window> window)
    {
        auto name = attributes["name"];

        if(elementName == "Font")
        {
            std::string src;
            float size = 12.0f;

            if(attributes.find("src") != attributes.end())
            {
                src = attributes["src"];
                if(attributes.find("size") != attributes.end() &&
                    IsFloat(attributes["size"]))
                    size = std::stof(attributes["size"]);

                window->AddFont(src, size, name);
            }
            else
            {
                throw ParsingException(R"(Missing "src" attribute from element "Font")");
            }
        }

        else if(elementName == "Style")
        {
            if(attributes.find("src") != attributes.end())
            {
                m_stylesParser->ParseFromFile(attributes["src"], m_mistakes);
            }
            else if(!content.empty())
            {
                m_stylesParser->ParseFromCode(content, m_mistakes);
            }
        }

        else if(elementName == "Title")
        {
            if(!content.empty())
            {
                window->SetTitle(content);
            }
        }

        else if(elementName == "WindowData")
        {
            int width = 0, height = 0;
            bool fullscreen = false, titleBar = true;

            if(attributes.find("width") != attributes.end())
                width = StrToInt(attributes["width"]);

            if(attributes.find("height") != attributes.end())
                height = StrToInt(attributes["height"]);

            if(attributes.find("fullscreen") != attributes.end())
                fullscreen = StrToBool(attributes["fullscreen"]);

            if(attributes.find("titlebar") != attributes.end())
                titleBar = StrToBool(attributes["titlebar"]);

            window->SetWidth(width);
            window->SetHeight(height);
            window->ToggleWindowOptions(fullscreen, titleBar);
        }
    }

    std::string ViewParser::GetElementName(const std::string &elementName, const std::unordered_map<std::string, std::string> &attributes, std::string& content)
    {
        if(attributes.find("name") != attributes.end())
            return attributes.at("name");

        if(!content.empty())
            return content;

        std::stringstream ss;
        ss << "##" << elementName << (++m_nameCounter);

        return ss.str();
    }

    std::shared_ptr<GuiElement> ViewParser::CreateFromName(std::shared_ptr<GuiElement> parent, const std::string &elementName, std::unordered_map<std::string, std::string>& attributes, std::shared_ptr<Window> window, std::string content)
    {
        auto name = std::move(GetElementName(elementName, attributes, content));
        auto id = attributes.find("id") == attributes.end() ? "" : attributes["id"];
        std::shared_ptr<GuiElement> element;

        if(elementName == "MainDockSpace")
        {
            auto dockspaceId = 1;
            auto saveLayout = true;

            if(attributes.find("dockspaceId") != attributes.end())
                dockspaceId = StrToInt(attributes["dockspaceId"]);

            if(attributes.find("saveLayout") != attributes.end())
                saveLayout = StrToBool(attributes["saveLayout"]);

            element = MainDockSpace::CreateMainDockSpace(std::move(name), dockspaceId, saveLayout);
        }

        else if(elementName == "StackSpace")
        {
            element = StackSpace::CreateStackSpace(std::move(name));
        }

        else if(elementName == "WindowContainer")
        {
            element = WindowContainer::CreateWindowContainer(std::move(parent), std::move(name));
        }

        else if(elementName == "Radio")
        {
            const char separator = '\n';

            std::vector<std::string> options;
            {
                std::istringstream iss(content);
                std::string option;
                while (std::getline(iss, option, separator))
                {
                    options.push_back(option);
                }
            }

            auto radio = Radio::CreateRadio(std::move(parent), std::move(name));
            for(const auto &option : options)
            {
                radio->AddOption(option);
            }

            element = std::move(radio);

        }

        else if(elementName == "Combo")
        {
            element = Combo::CreateCombo(std::move(parent), std::move(name));
        }

        else if(elementName == "Button")
        {
            element = Button::CreateButton(std::move(parent), std::move(name));
        }

        else if(elementName == "Text")
        {
            auto wrapped = !(attributes.find("wrapped") != attributes.end()) || (attributes["wrapped"] != "false");
            element = Text::CreateText(std::move(parent), std::move(name), wrapped);
        }

        else if(elementName == "Checkbox")
        {
            element = Checkbox::CreateCheckbox(std::move(parent), std::move(name));
        }

        else if(elementName == "Table")
        {
            const char separator = ';';
            auto headersList = attributes["headers"];

            std::vector<std::string> headers;
            {
                std::istringstream iss(headersList);
                std::string header;
                while (std::getline(iss, header, separator))
                {
                    headers.push_back(header);
                }
            }

            element = Table::CreateTable(std::move(parent), std::move(name), headers);
        }

        else if(elementName == "TextInput")
        {
            element = TextInput::CreateTextInput(std::move(parent), std::move(name));
        }

        else if(elementName == "TextArea")
        {
            element = TextArea::CreateTextArea(std::move(parent), std::move(name));
        }

        else if(elementName == "Option")
        {
            element = SelectorOption::CreateSelectorOption(std::move(parent), std::move(name));
        }

        else if(elementName == "TableRow")
        {
            element = TableRow::CreateTableRow(std::move(parent), std::move(name));
        }

        else if(elementName == "TopMenu")
        {
            element = TopMenu::CreateTopMenu(std::move(name));
        }

        else if(elementName == "SubMenu")
        {
            element = SubMenu::CreateSubMenu(std::move(parent), std::move(name));
        }

        else if(elementName == "MenuOption")
        {
            std::string shortcut;

            if(attributes.find("shortcut") != attributes.end())
                shortcut = attributes["shortcut"];

            element = MenuOption::CreateMenuOption(std::move(parent), std::move(name), shortcut);
        }

        else if(elementName == "Separator")
        {
            element = Separator::CreateSeparator(std::move(parent), std::move(name));
        }

        else if(elementName == "SliderFloat")
        {
            element = SliderFloat::CreateSliderFloat(std::move(parent), std::move(name));

            if(attributes.find("min") != attributes.end())
                ((SliderFloat*)element.get())->SetMin(StrToFloat(attributes["min"]));

            if(attributes.find("max") != attributes.end())
                ((SliderFloat*)element.get())->SetMax(StrToFloat(attributes["max"]));
        }

        else if(elementName == "SliderInt")
        {
            element = SliderInt::CreateSliderInt(std::move(parent), std::move(name));

            if(attributes.find("min") != attributes.end())
                ((SliderInt*)element.get())->SetMin(StrToInt(attributes["min"]));

            if(attributes.find("max") != attributes.end())
                ((SliderInt*)element.get())->SetMax(StrToInt(attributes["max"]));
        }

        else if(elementName == "ColorPicker")
        {
            element = ColorPicker::CreateColorPicker(std::move(parent), std::move(name));

            if(attributes.find("preview") != attributes.end())
                ((ColorPicker*)element.get())->TogglePreview(StrToBool(attributes["preview"]));

            if(attributes.find("input") != attributes.end())
                ((ColorPicker*)element.get())->ToggleInput(StrToBool(attributes["input"]));
        }

        //---

        if(element)
        {
            if(!id.empty())
                window->AddElementId(id, element);

            return element;
        }
        else
        {
            std::stringstream ss;
            ss << "Unknown element \"" << elementName << "\"";
            throw ParsingException(ss.str().c_str());
        }
    }

    float ViewParser::StrToFloat(const std::string &str)
    {
        float val = 0;
        std::stringstream ss;
        ss << str;
        ss >> val;

        return val;
    }

    int ViewParser::StrToInt(const std::string &str)
    {
        int integer = 0;
        std::stringstream ss;
        ss << str;
        ss >> integer;

        return integer;
    }

    bool ViewParser::StrToBool(const std::string &str)
    {
        return str == "true";
    }

    void ViewParser::TryAddLayout(const std::shared_ptr<GuiElement>& element, const std::shared_ptr<Window>& window)
    {
        if(IsType<Layout>(element))
        {
            std::shared_ptr<Layout> newLayout = std::dynamic_pointer_cast<Layout>(element);
            window->SetLayout(newLayout);
        }
        else
        {
            throw ParsingException("Root element should be layout");
        }
    }

    void ViewParser::TryAddAsChild(const std::shared_ptr<GuiElement> &container, const std::shared_ptr<GuiElement> &element, const std::string &elementName)
    {
        if (auto* c = dynamic_cast<Container*>(container.get()))
        {
            c->AddChild(element);
        }
        else
        {
            std::stringstream ss;
            ss << "Tried to append to non container element: [" << elementName <<  "]";
            throw ParsingException(ss.str().c_str());
        }
    }

    void ViewParser::TryAddToLayout(const std::shared_ptr<GuiElement>& element,
                                    const std::shared_ptr<GuiElement> &container,
                                    std::unordered_map<std::string, std::string>& attributes,
                                    const std::shared_ptr<Window>& window)
    {
        if(dynamic_cast<Container*>(element.get()) == nullptr)
            throw ParsingException("Only Container can fit into layout");

        std::shared_ptr<Container> newContainer = std::dynamic_pointer_cast<Container>(element);

        if(auto* layout = dynamic_cast<Layout*>(container.get()))
        {
            if(IsType<TopMenu>(element))
            {
                auto menu = std::dynamic_pointer_cast<TopMenu>(newContainer);
                window->SetTopMenu(menu);
                return;
            }

            try
            {
                layout->AddContainer(newContainer, attributes, window);
            }
            catch(const LayoutException& e)
            {
                throw ParsingException(e.what());
            }
        }
        else
        {
            throw ParsingException("Tried to append container to non-layout element");
        }
    }

    void ViewParser::TryAddTopMenu(const std::shared_ptr<GuiElement> &element, const std::shared_ptr<Window> &window)
    {
        if(IsType<TopMenu>(element))
        {
            std::shared_ptr<TopMenu> newMenu = std::dynamic_pointer_cast<TopMenu>(element);
            window->SetTopMenu(newMenu);
        }
        else
        {
            throw ParsingException("Type mismatch to top menu item!");
        }
    }
}