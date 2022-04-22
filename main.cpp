#include <string>
#include <regex>
#include <fstream>
#include <iostream>
#include "Trema/View/SDL2/SDL2Window.h"
#include "Trema/View/Components/Widgets/Button.h"
#include "Trema/View/Components/Widgets/Text.h"
#include "Trema/View/Components/Widgets/Table.h"
#include "Trema/View/Components/Widgets/Input/TextInput.h"
#include "Trema/View/Parser/TinyXML/TinyXMLViewParser.h"
#include "Trema/View/Components/Windows/FileDialog.h"
#include "Trema/View/Style/Tokenizer/Tokenizer.h"
#include "Trema/View/Style/StackedStyleParser.h"
#include "Trema/View/Components/Widgets/ColorPicker.h"

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
    auto info = WindowInfo { .Title = "Trema", .SecondsPerUpdate = 0.01, .Width = 1280, .Height = 720 };
    auto stylesParser = std::make_unique<StackedStyleParser>();
    auto parser = TinyXMLViewParser(std::move(stylesParser));
    auto window = SDL2Window::CreateSDL2Window(info);

    window->AddPopupComponent<FileDialog>(FileDialog::CreateFileDialog("File dialog"));

    parser.SetupWindowFromFile("./sample_1.txml", window);
    auto mistakes = parser.GetMistakes();

    int id = 0;

    auto nameInput = window->GetElementById<TextInput>("nameInput");
    auto scoreInput = window->GetElementById<TextInput>("scoreInput");

    auto scoresBoard = window->GetElementById<Table>("scoresBoard");

    auto addButton = window->GetElementById<Button>("addButton");

    addButton->AddOnClickListener("pute", [&nameInput, &scoreInput, &id, &scoresBoard](const Trema::View::Button &)
    {
        auto newId = ++id;
        auto name = nameInput->GetText();
        auto score = scoreInput->GetText();

        std::stringstream ss;
        ss << newId;

        auto row = TableRow::CreateTableRow(scoresBoard, name);
        row->AddChild(Text::CreateText(row, ss.str(), true));
        row->AddChild(Text::CreateText(row, name, true));
        row->AddChild(Text::CreateText(row, score));

        scoresBoard->AddValue(std::move(row));
    });

    auto colorPicker = window->GetElementById<ColorPicker>("colors");
    colorPicker->AddOnChangeListener("pute", [](const Trema::View::ColorPicker &cp)
    {
        std::cout << cp.GetColorInt() << std::endl;
    });

    /*for(const auto &mistake : mistakes)
    {
        std::cerr << mistake << "\n";
    }

    std::cout << std::endl;*/

    /*auto newFile = window->GetElementById<MenuOption>("newFile");

    if(newFile)
    {
        newFile->AddOnClickListener("pute", [&window](const Trema::View::MenuOption &)
        {
             window->GetComponent<FileDialog>()->ShowFileDialog("./", ".pdf", [](const std::string &path)
                {
                    std::cout << path << std::endl;
                }, Trema::View::Files);
        });
    }*/

    window->Run();

    return EXIT_SUCCESS;
}
