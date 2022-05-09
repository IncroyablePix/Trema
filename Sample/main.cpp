#include <string>
#include <regex>
#include <fstream>
#include <iostream>
#include <View/Components/Widgets/Input/TextInput.h>
#include <View/Components/Widgets/Sliders/SliderInt.h>
#include <View/Components/Widgets/Options/Radio.h>
#include <View/Components/Widgets/ColorPicker.h>
#include <View/Components/Widgets/Options/Combo.h>
#include <View/Components/Widgets/DataContainers/Table.h>
#include <View/Components/Widgets/Button.h>
#include <View/Components/TopMenu/MenuOption.h>
#include <View/Style/Parser/StackedStyleParser.h>
#include <View/Parser/TinyXML/TinyXMLViewParser.h>
#include <View/Components/Windows/FileDialog.h>
#include "View/Components/Widgets/Pure/Text.h"
#include <View/Windowing/GLFW/GLFWWindow.h>

using namespace Trema::View;

/*void SetDarkStyle()
{
    ImGuiStyle * style = &ImGui::GetStyle();

    style->WindowPadding = ImVec2(15, 15); // Done
    style->WindowRounding = 5.0f; // Done
    style->FramePadding = ImVec2(5, 5); // Done
    style->FrameRounding = 4.0f; // Done
    style->ItemSpacing = ImVec2(12, 8);
    style->ItemInnerSpacing = ImVec2(8, 6);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 15.0f;
    style->ScrollbarRounding = 9.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;

    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f); // Done
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f); // Done
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f); // Done
    //style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f); // Done
    style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f); // Done
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f); // Done
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f); // Done
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f); // Done
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
    style->Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f); // Done
    //style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

std::vector<std::string> split(const std::string& input, const std::string& regex)
{
    std::regex re(regex);
    std::sregex_token_iterator first{input.begin(), input.end(), re, -1}, last;
    return {first, last};
}*/

int main(int argc, char** argv)
{
    auto info = WindowInfo { .Width = 1280, .Height = 720 };
    auto window = GLFWWindow::CreateGLFWWindow(info);
    auto stylesParser = std::make_unique<StackedStyleParser>();
    auto parser = TinyXMLViewParser(std::move(stylesParser));

    window->AddPopupComponent<FileDialog>(FileDialog::CreateFileDialog("Export..."));
    parser.LoadView("./people_view.txml", window);

    // Fields
    auto count = 0;
    auto firstNameField = window->GetElementById<TextInput>("firstName");
    auto lastNameField = window->GetElementById<TextInput>("lastName");
    auto heightField = window->GetElementById<SliderInt>("height");
    auto sexField = window->GetElementById<Radio>("sex");
    auto favouriteColourField = window->GetElementById<ColorPicker>("favouriteColour");
    auto diplomaField = window->GetElementById<Combo>("diploma");

    // Buttons & Table
    auto peopleGrid = window->GetElementById<Table>("peopleGrid");
    auto addPersonButton = window->GetElementById<Button>("addPerson");
    auto clearButton = window->GetElementById<Button>("clear");

    // Menu
    auto quitOption = window->GetElementById<MenuOption>("quit");
    auto saveOption = window->GetElementById<MenuOption>("save");

    // Data
    std::stringstream data;
    data << "First name;Last name;Height;Sex;Favourite colour;Diploma\n";

    // Listener
    addPersonButton->AddOnClickListener("Add", [&count, &lastNameField, &firstNameField, &heightField, &sexField, &favouriteColourField, &diplomaField, &peopleGrid, &data](const Trema::View::Button &)
    {
        auto newId = ++count;
        std::stringstream ss;
        ss << newId;

        auto firstName = firstNameField->GetText();
        auto lastName = lastNameField->GetText();
        auto height = heightField->GetValue();
        auto sex = sexField->GetOption();
        auto favouriteColour = favouriteColourField->GetColorInt() | 0xFF; // Full blast alpha!
        auto diploma = diplomaField->GetOption();

        auto row = TableRow::CreateTableRow(peopleGrid, ss.str());
        row->AddChild(Text::CreateText(row, firstName, true));
        row->AddChild(Text::CreateText(row, lastName, true));

        ss.str("");
        ss << height << " cm";
        row->AddChild(Text::CreateText(row, ss.str(), true));
        row->AddChild(Text::CreateText(row, sex, true));

        auto colorText = Text::CreateText(row, "=====", true);
        colorText->Style.TextColor().SetColor(favouriteColour);
        row->AddChild(colorText);

        row->AddChild(Text::CreateText(row, diploma, true));

        data << firstName << ";"
            << lastName << ";"
            << std::dec << height << " cm;"
            << sex << ";"
            << std::hex << favouriteColour << ";"
            << diploma << "\n";

        peopleGrid->AddValue(row);
    });

    quitOption->AddOnClickListener("Quit", [&window](const Trema::View::MenuOption &)
    {
        window->Close();
    });

    saveOption->AddOnClickListener("Save", [&window, &data](const Trema::View::MenuOption &)
    {
        window->GetComponent<FileDialog>()->ShowFileDialog("./", ".csv", [&data](const std::string &path)
        {
            std::stringstream filePath;
            filePath << path;

            if(path.find(".csv", path.length() - 5) == std::string::npos)
                filePath << ".csv";

            std::ofstream output(filePath.str());
            output << data.str();
        }, Trema::View::SaveFile);
    });

    window->Run();

    return EXIT_SUCCESS;
}
