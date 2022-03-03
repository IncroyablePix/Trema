#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include "View/SDL2/SDL2Window.h"
#include "View/Components/Docking/MainDockSpace.h"
#include "View/Components/Container/WindowContainer.h"
#include "View/Components/Widgets/Button.h"
#include "View/Components/Widgets/Options/Radio.h"
#include "View/Components/Widgets/Options/Combo.h"
#include "View/Components/Widgets/Text.h"
#include "View/Components/Widgets/Checkbox.h"
#include "View/Components/Widgets/Table.h"
#include "View/Components/Widgets/Input/TextInput.h"
#include "View/Components/Widgets/Input/TextArea.h"
#include "View/Parser/TinyXML/TinyXMLViewParser.h"
#include "View/Components/Windows/FileDialog.h"

using namespace Trema::View;

std::vector<std::string> split(const std::string& input, const std::string& regex)
{
    std::regex re(regex);
    std::sregex_token_iterator first{input.begin(), input.end(), re, -1}, last;
    return {first, last};
}

int main(int argc, char** argv)
{
    WindowInfo info { .Title = "Trema", .SecondsPerUpdate = 0.01, .Width = 1280, .Height = 720 };

    auto parser = TinyXMLViewParser();
    auto window = SDL2Window::CreateSDL2Window(info);
    //parser.SetupWindowFromFile("./csv_table.txml", window);
    //window->AddPopupComponent<FileDialog>(FileDialog::CreateFileDialog("File dialog"));
    //window->SetDefaultFont("./BAUHS93.TTF", 14.0f);

    //---

    /*auto tableContainer = window->GetElementById<WindowContainer>("table-container");
    auto button = window->GetElementById<Button>("test-button");

    button->AddOnClickListener("open-file", [&window](const Trema::View::Button &)
    {
        window->GetComponent<FileDialog>()->ShowFileDialog("C:\\", "*.*",  [](const std::string &path)
        {
            std::cout << path <<  std::endl;
            ImGuiStyle * style = &ImGui::GetStyle();

            style->WindowPadding = ImVec2(15, 15);
            style->WindowRounding = 5.0f;
            style->FramePadding = ImVec2(5, 5);
            style->FrameRounding = 4.0f;
            style->ItemSpacing = ImVec2(12, 8);
            style->ItemInnerSpacing = ImVec2(8, 6);
            style->IndentSpacing = 25.0f;
            style->ScrollbarSize = 15.0f;
            style->ScrollbarRounding = 9.0f;
            style->GrabMinSize = 5.0f;
            style->GrabRounding = 3.0f;

            style->Colors[ImGuiCol_Text] = ImColor();
            style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f); // text color
            style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f); // disabled text
            style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
            //style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
            style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
            style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
            style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
            style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
            style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
            style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
            style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
            style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
            style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
            style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
            style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
            style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
            style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
            style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
            //style->Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
            style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
            style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
            style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
            style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
            style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
            style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
            style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
            style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
            style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
            //style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
            //style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
            //style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
            style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
            style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
            //style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
            //style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
            //style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
            style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
            style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
            style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
            style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
            style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
            //style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
        });
    });

    // CSV
    auto file = std::fstream();

    file.open("./cities.csv", std::ios::in);
    if(file.is_open())
    {
        std::string line;
        std::vector<std::string> vals;

        getline(file, line);
        vals = split(line, ";");

        auto table = Table::CreateTable(tableContainer, "Cities", vals);
        auto i = 0;

        while(std::getline(file, line))
        {
            vals = split(line, ";");
            auto row = TableRow::CreateTableRow(table, std::to_string(++i));

            for(const auto &val : vals)
            {
                row->AddChild(Text::CreateText(row, val));
            }

            table->AddValue(row);
        }

        tableContainer->AddChild(table);
    }
    else
    {
        tableContainer->AddChild(Text::CreateText(tableContainer, "Could not open file \"cities.csv\"."));
    }*/

    //--- Table

    parser.SetupWindowFromFile("./sample_1.txml", window);

    auto counter = 1;
    auto scoresBoard = window->GetElementById<Table>("scoresBoard");
    auto nameInput = window->GetElementById<TextInput>("nameInput");
    auto scoreInput = window->GetElementById<TextInput>("scoreInput");
    auto addButton = window->GetElementById<Button>("addButton");

    auto textOutput = window->GetElementById<Text>("textOutput");
    auto combo = window->GetElementById<Combo>("my-combo");

    addButton->AddOnClickListener("addButtonListener", [&counter, &scoresBoard, nameInput, scoreInput](const Trema::View::Button &button)
    {
        auto id = std::to_string(counter);
        auto name = std::move(nameInput->GetText());
        auto score = std::move(scoreInput->GetText());
        auto row = TableRow::CreateTableRow(scoresBoard, std::string(id));

        row->Elements.push_back(Text::CreateText(row, id));
        row->Elements.push_back(Text::CreateText(row, name));
        row->Elements.push_back(Text::CreateText(row, score));

        scoresBoard->AddValue(row);

        nameInput->SetText("");
        scoreInput->SetText("");

        counter ++;
    });
    /*textInput->AddOnChangeListener("main", [&textOutput](const std::string &text)
    {
        textOutput->SetName(text);
    });*/

    window->Run();

    /*auto dockSpaceLayout = MainDockSpace::CreateMainDockSpace("Dockspace", 1);
    auto topMenu = TopMenu::CreateTopMenu("Top Menu");
    auto container = WindowContainer::CreateWindowContainer(dockSpaceLayout, "Test");

    auto radio = Radio::CreateRadio(container, "My radio");
    radio->AddOption("Fuck", [](const Radio& r) { });
    radio->AddOption("Me", [](const Radio& r) { });
    radio->AddOption("Jesus", [](const Radio& r) { });

    auto combo = Combo::CreateCombo(container, "Orientation");
    combo->AddOption("Column", [&radio](const Combo& combo)
    {
        radio->Style.Orientation = Column;
    });
    combo->AddOption("Row", [&radio](const Combo& combo)
    {
        radio->Style.Orientation = Row;
    });

    auto button = Button::CreateButton(container, "My test button");
    button->AddOnClickListener("listener 1", [](const Button& button)
    {
        ImGuiStyle * style = &ImGui::GetStyle();

        style->WindowPadding = ImVec2(15, 15);
        style->WindowRounding = 5.0f;
        style->FramePadding = ImVec2(5, 5);
        style->FrameRounding = 4.0f;
        style->ItemSpacing = ImVec2(12, 8);
        style->ItemInnerSpacing = ImVec2(8, 6);
        style->IndentSpacing = 25.0f;
        style->ScrollbarSize = 15.0f;
        style->ScrollbarRounding = 9.0f;
        style->GrabMinSize = 5.0f;
        style->GrabRounding = 3.0f;

        style->Colors[ImGuiCol_Text] = ImColor();
        style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f); // text color
        style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f); // disabled text
        style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        //style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
        style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
        style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
        style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        //style->Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
        style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        //style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        //style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        //style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        //style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
        //style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
        //style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
        style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
        //style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
    });

    auto buttonBob = Button::CreateButton(container, "c quoi");
    auto text = Text::CreateText(container, "La vérité c'est que");
    buttonBob->AddOnClickListener("listener 1", [&text](const Button& button)
    {
        text->SetName("Benjam' est une pute");
    });

    auto checkbox = Checkbox::CreateCheckbox(container, u8"baise ma mère ?");
    checkbox->AddOnCheckListener("Benz", [&text](const Checkbox& box, bool checked)
    {
        if(checked)
            text->SetName(u8"Benjam' est un BG");
        else
            text->SetName(u8"Benjam' est un énorme BG");
    });

    auto table = Table<4>::CreateTable(container, "My Table", { "Id", "Name", "Value", "Baiser"});
    table->AddValue(TableRow<4>(std::array<std::shared_ptr<IGuiElement>, 4>({Text::CreateText(table, "1"), Text::CreateText(table, "JajaFil"), Text::CreateText(table, "0.751"), Button::CreateButton(table, "Baiser")})));
    table->AddValue(TableRow<4>(std::array<std::shared_ptr<IGuiElement>, 4>({Text::CreateText(table, "2"), Text::CreateText(table, "BobLaPute"), Text::CreateText(table, "0.488"), Button::CreateButton(table, "Baiser")})));
    table->AddValue(TableRow<4>(std::array<std::shared_ptr<IGuiElement>, 4>({Text::CreateText(table, "3"), Text::CreateText(table, "Maxoupe"), Text::CreateText(table, "0.1465987"), Button::CreateButton(table, "Baiser")})));

    auto repeaterText = Text::CreateText(container, "I don't know yet");
    auto inputText = TextInput::CreateTextInput(container, "My input", "Salut le fuck");
    auto textArea = TextArea::CreateTextArea(container, "My TextArea", "Baiser ma mère,\nUne passion qui m'a pris tôt.");

    inputText->AddOnChangeListener("fouk", [&repeaterText](std::string text)
    {
        repeaterText->SetName(std::move(text));
    });

    container->AddChild(button);
    container->AddChild(combo);
    container->AddChild(radio);
    container->AddChild(buttonBob);
    container->AddChild(text);
    container->AddChild(checkbox);
    container->AddChild(table);
    container->AddChild(inputText);
    container->AddChild(textArea);
    container->AddChild(repeaterText);

    dockSpaceLayout->AddElement(container, DockSlot::DOCK_TOP);
    window->SetTopMenu(topMenu);
    window->SetLayout(dockSpaceLayout);*/
}
