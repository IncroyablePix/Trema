//
// Created by JajaFil on 2/18/2022.
//

#include <sstream>
#include <iterator>
#include <vector>
#include "IViewParser.h"
#include "../Components/Docking/MainDockSpace.h"
#include "../Components/Container/WindowContainer.h"
#include "../Components/Widgets/Options/Radio.h"
#include "../Components/Widgets/Options/Combo.h"
#include "../Components/Widgets/Button.h"
#include "../Components/Widgets/Text.h"
#include "../Components/Widgets/Checkbox.h"
#include "../Components/Widgets/Table.h"
#include "../Components/Widgets/Input/TextInput.h"
#include "../Components/Widgets/Input/TextArea.h"
#include "../Exceptions/ParsingException.h"
#include "../Components/Widgets/Options/SelectorOption.h"
#include "../Utils/StringExtensions.h"
#include "../Components/TopMenu/SubMenu.h"
#include "../Components/TopMenu/MenuOption.h"
#include "../Components/Widgets/Separator.h"

namespace Trema::View
{
    void IViewParser::HeadElementFromName(const std::string& elementName, std::unordered_map<std::string, std::string>& attributes, std::shared_ptr<IWindow> window)
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
    }

    std::shared_ptr<IGuiElement> IViewParser::CreateFromName(std::shared_ptr<IGuiElement> parent, const std::string &elementName, std::unordered_map<std::string, std::string>& attributes, std::shared_ptr<IWindow> window, std::string content)
    {
        auto name = attributes["name"];
        auto id = attributes.find("id") == attributes.end() ? "" : attributes["id"];
        std::shared_ptr<IGuiElement> element;

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

        else if(elementName == "TopMenu")
        {
            element = TopMenu::CreateTopMenu(std::move(name));
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

    int IViewParser::StrToInt(const std::string &str)
    {
        int integer = 0;
        std::stringstream ss;
        ss << str;
        ss >> integer;

        return integer;
    }

    bool IViewParser::StrToBool(const std::string &str)
    {
        return str == "true";
    }

    void IViewParser::TryAddLayout(const std::shared_ptr<IGuiElement>& element, const std::shared_ptr<IWindow>& window)
    {
        if(IsType<ILayout>(element))
        {
            std::shared_ptr<ILayout> newLayout = std::dynamic_pointer_cast<ILayout>(element);
            window->SetLayout(newLayout);
        }
        else
        {
            throw ParsingException("Root element should be layout");
        }
    }

    void IViewParser::TryAddAsChild(const std::shared_ptr<IGuiElement> &container, const std::shared_ptr<IGuiElement> &element, const std::string &elementName)
    {
        if (auto* c = dynamic_cast<IContainer*>(container.get()))
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

    void IViewParser::TryAddToLayout(const std::shared_ptr<IGuiElement>& element,
                                           const std::shared_ptr<IGuiElement> &container,
                                           std::unordered_map<std::string, std::string>& attributes,
                                           const std::shared_ptr<IWindow>& window)
    {
        if (auto* layout = dynamic_cast<DockSpace*>(container.get()))
        {
            if(dynamic_cast<IContainer*>(element.get()) == nullptr)
            {
                throw ParsingException("Only IContainer can fit into layout");
            }

            std::shared_ptr<IContainer> newContainer = std::dynamic_pointer_cast<IContainer>(element);

            if(attributes.find("dockSlot") != attributes.end())
            {
                auto dockSlotName = attributes["dockSlot"];
                auto dockSlot = DockSlotFromString(dockSlotName);

                layout->AddElement(std::move(newContainer), dockSlot);
            }
            else if(IsType<TopMenu>(element))
            {
                auto menu = std::dynamic_pointer_cast<TopMenu>(element);
                window->SetTopMenu(menu);
            }
            else
            {
                throw ParsingException("Missing attribute \"dockSlot\" for DockSpace child");
            }
        }
        else
        {
            throw ParsingException("Unsupported layout type");
        }
    }

    void IViewParser::TryAddTopMenu(const std::shared_ptr<IGuiElement> &element, const std::shared_ptr<IWindow> &window)
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