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

    auto clear = [&lastNameField, &firstNameField, &heightField, &sexField, &diplomaField]()
            {
                firstNameField->SetText("");
                lastNameField->SetText("");
                heightField->SetValue(50);
                sexField->SetOption(0);
                diplomaField->SetOption("");
            };

    clearButton->AddOnClickListener("Quit", [&clear](const Button& b)
    {
        clear();
    });

    // Listener
    addPersonButton->AddOnClickListener("Add", [&count, &lastNameField, &firstNameField, &heightField, &sexField, &favouriteColourField, &diplomaField, &peopleGrid, &data, &clear](const Trema::View::Button &)
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
        clear();
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
