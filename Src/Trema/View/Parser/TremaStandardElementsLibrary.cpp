#include "TremaStandardElementsLibrary.h"
#include "../Activities/Activity.h"
#include "../Components/Layout/Docking/MainDockSpace.h"
#include "../../Utils/StringConversion.h"
#include "../Components/Layout/StackSpace/StackSpace.h"
#include "../Components/Container/WindowContainer.h"
#include "../Components/Widgets/Options/Radio.h"
#include "../Components/Widgets/Options/Combo.h"
#include "../Components/Widgets/Button.h"
#include "../Components/Widgets/Pure/Text.h"
#include "../Components/Widgets/Checkbox.h"
#include "../Components/Widgets/DataContainers/Table.h"
#include "../Components/Widgets/Input/TextInput.h"
#include "../Components/Widgets/Input/TextArea.h"
#include "../Components/Widgets/Options/SelectorOption.h"
#include "../Components/TopMenu/SubMenu.h"
#include "../Components/TopMenu/MenuOption.h"
#include "../Components/Widgets/Pure/Separator.h"
#include "../Components/Widgets/Sliders/SliderFloat.h"
#include "../Components/Widgets/Sliders/SliderInt.h"
#include "../Components/Widgets/ColorPicker.h"
#include "../Components/Widgets/Pure/Image/Image.h"
#include "../Exceptions/ParsingException.h"
#include "MissingAttributeException.h"

namespace Trema::View
{
    void TremaStandardElementsLibrary::AddElements(ViewParser &viewParser)
    {
        AddHeadElements(viewParser);
        AddBodyElements(viewParser);
    }

    void TremaStandardElementsLibrary::AddBodyElements(ViewParser &viewParser)
    {
        viewParser.AddBodyElementCreator("MAINDOCKSPACE", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            auto dockspaceId = 1;
            auto saveLayout = true;

            if(attributes.contains("dockspaceId"))
                dockspaceId = Utils::StrToInt(attributes["dockspaceId"]);

            if(attributes.contains("saveLayout"))
                saveLayout = Utils::StrToBool(attributes["saveLayout"]);

            return MainDockSpace::CreateMainDockSpace(std::move(name), saveLayout);
        });

        viewParser.AddBodyElementCreator("STACKSPACE", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            return StackSpace::CreateStackSpace(std::move(name));
        });

        viewParser.AddBodyElementCreator("WINDOWCONTAINER", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            return WindowContainer::CreateWindowContainer(std::move(parent), std::move(name));
        });

        viewParser.AddBodyElementCreator("RADIO", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
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

            return std::move(radio);
        });

        viewParser.AddBodyElementCreator("COMBO", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            return Combo::CreateCombo(std::move(parent), std::move(name));
        });

        viewParser.AddBodyElementCreator("BUTTON", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            return Button::CreateButton(std::move(parent), std::move(name));
        });

        viewParser.AddBodyElementCreator("TEXT", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            auto wrapped = !(attributes.contains("wrapped")) || (attributes["wrapped"] != "false");
            auto text = Text::CreateText(std::move(parent), std::move(name), wrapped);
            return std::move(text);
        });

        viewParser.AddBodyElementCreator("CHECKBOX", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            return Checkbox::CreateCheckbox(std::move(parent), std::move(name));
        });

        viewParser.AddBodyElementCreator("TABLE", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
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

            return Table::CreateTable(std::move(parent), std::move(name), headers);
        });

        viewParser.AddBodyElementCreator("TEXTINPUT", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            auto password = attributes.contains("type") && attributes["type"] == "password";
            auto element = TextInput::CreateTextInput(std::move(parent), std::move(name));
            element->SetPassword(password);

            return std::move(element);
        });

        viewParser.AddBodyElementCreator("TEXTAREA", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            return TextArea::CreateTextArea(std::move(parent), std::move(name));
        });

        viewParser.AddBodyElementCreator("OPTION", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            return SelectorOption::CreateSelectorOption(std::move(parent), std::move(name));
        });

        viewParser.AddBodyElementCreator("TABLEROW", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            return TableRow::CreateTableRow(std::move(parent), std::move(name));
        });

        viewParser.AddBodyElementCreator("TOPMENU", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            return TopMenu::CreateTopMenu(std::move(name));
        });

        viewParser.AddBodyElementCreator("SUBMENU", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            return SubMenu::CreateSubMenu(std::move(parent), std::move(name));
        });

        viewParser.AddBodyElementCreator("MENUOPTION", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            std::string shortcut;

            if(attributes.contains("shortcut"))
                shortcut = attributes["shortcut"];

            return MenuOption::CreateMenuOption(std::move(parent), std::move(name), shortcut);
        });

        viewParser.AddBodyElementCreator("SEPARATOR", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            return Separator::CreateSeparator(std::move(parent), std::move(name));
        });

        viewParser.AddBodyElementCreator("SLIDERFLOAT", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            auto element = SliderFloat::CreateSliderFloat(std::move(parent), std::move(name));

            if(attributes.contains("min"))
                element->SetMin(Utils::StrToFloat(attributes["min"]));

            if(attributes.contains("max"))
                element->SetMax(Utils::StrToFloat(attributes["max"]));

            return std::move(element);
        });

        viewParser.AddBodyElementCreator("SLIDERINT", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            auto element = SliderInt::CreateSliderInt(std::move(parent), std::move(name));

            if(attributes.contains("min"))
                element->SetMin(Utils::StrToInt(attributes["min"]));

            if(attributes.contains("max"))
                element->SetMax(Utils::StrToInt(attributes["max"]));

            return std::move(element);
        });

        viewParser.AddBodyElementCreator("COLORPICKER", [](
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content) -> std::shared_ptr<GuiElement>
        {
            auto element = ColorPicker::CreateColorPicker(std::move(parent), std::move(name));

            if(attributes.contains("preview"))
                element->TogglePreview(Utils::StrToBool(attributes["preview"]));

            if(attributes.contains("input"))
                element->ToggleInput(Utils::StrToBool(attributes["input"]));

            return std::move(element);
        });

        viewParser.AddBodyElementCreator("IMAGE", [](
             std::shared_ptr<GuiElement> parent,
             std::string name,
             std::unordered_map<std::string, std::string> &attributes,
             std::shared_ptr<Window> window,
             Activity &activity,
             std::string content) -> std::shared_ptr<GuiElement>
        {
            std::string src;

            if(attributes.contains("src"))
                src = attributes["src"];

            std::shared_ptr<IRenderImage> imageRender = window->AddImage(name, src);

            return Image::CreateImage(std::move(parent), std::move(name), std::move(imageRender));
        });
    }

    void TremaStandardElementsLibrary::AddHeadElements(ViewParser &viewParser)
    {
        viewParser.AddHeadElementCreator("FONT", [](
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                IStyleParser &styleApplier,
                std::string content)
        {
            std::string src;
            float size = 12.0f;

            if(attributes.contains("src"))
            {
                src = attributes["src"];
                if(attributes.contains("size") &&
                   Utils::IsFloat(attributes["size"]))
                    size = std::stof(attributes["size"]);

                window->AddFont(src, size, name);
            }
            else
            {
                throw MissingAttributeException("Font is missing \"src\"");
            }
        });

        viewParser.AddHeadElementCreator("ICON", [](
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                IStyleParser &styleApplier,
                std::string content)
        {
            std::string src;
            if(attributes.contains("src"))
            {
                src = attributes["src"];
                window->SetWindowIcon(src);
            }
            else
            {
                throw MissingAttributeException("Icon is missing \"src\"");
            }
        });

        viewParser.AddHeadElementCreator("STYLE", [](
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                IStyleParser &styleApplier,
                const std::string& content)
        {
            if(attributes.contains("src"))
            {
                styleApplier.ParseFromFile(attributes["src"]);
            }
            else if(!content.empty())
            {
                styleApplier.ParseFromCode(content);
            }
        });

        viewParser.AddHeadElementCreator("TITLE", [](
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                IStyleParser &styleApplier,
                std::string content)
        {
            if(!content.empty())
            {
                window->SetTitle(content);
            }

            return nullptr;
        });

        viewParser.AddHeadElementCreator("WINDOWDATA", [](
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                IStyleParser &styleApplier,
                std::string content)
        {
            int width = 0, height = 0;
            bool fullscreen = false, titleBar = true;

            if(attributes.contains("width"))
                width = Utils::StrToInt(attributes["width"]);

            if(attributes.contains("height"))
                height = Utils::StrToInt(attributes["height"]);

            if(attributes.contains("fullscreen"))
                fullscreen = Utils::StrToBool(attributes["fullscreen"]);

            if(attributes.contains("titlebar"))
                titleBar = Utils::StrToBool(attributes["titlebar"]);

            activity.SetSize(width, height);
            activity.ToggleFullscreen(fullscreen);
            window->SetWidth(width);
            window->SetHeight(height);
            window->ToggleWindowOptions(fullscreen, titleBar);
        });
    }
}