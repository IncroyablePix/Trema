#include <regex>
#include <string>
#include <fstream>
#include <TremaProgram.h>
#include <View/Components/Widgets/CollectionView/VectorView.h>
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
#include <View/Components/Widgets/Pure/Text.h>
#include <View/Windowing/GLFW/GLFWWindow.h>
#include <View/Activities/Activity.h>
#include <View/Components/Container/WindowContainer.h>
#include <Observable/Collections/ObservableCollection.h>
#include <View/Windowing/WindowBuilder.h>

using namespace Trema::View;
using namespace Trema::Observable;

class PeopleActivity : public Activity
{
public:
    PeopleActivity(Intent intent, uint16_t requestCode = -1) : Activity(std::move(intent), requestCode)
    {

    }

    void OnCreateView() override
    {
        LoadView("./resources/views/people_view.txml");
    }

    void OnActivityStart() override
    {
        // Fields
        m_firstNameField = GetElementById<TextInput>("firstName");
        m_lastNameField = GetElementById<TextInput>("lastName");
        m_heightField = GetElementById<SliderInt>("height");
        m_sexField = GetElementById<Radio>("sex");
        m_favouriteColourField = GetElementById<ColorPicker>("favouriteColour");
        m_diplomaField = GetElementById<Combo>("diploma");

        // Buttons & Table
        m_peopleGrid = GetElementById<Table>("peopleGrid");
        m_addPersonButton = GetElementById<Button>("addPerson");
        m_clearButton = GetElementById<Button>("clear");

        // Menu
        m_quitOption = GetElementById<MenuOption>("quit");
        m_saveOption = GetElementById<MenuOption>("save");
        m_disconnectOption = GetElementById<MenuOption>("disconnect");

        // Data
        std::stringstream data;
        data << "First name;Last name;Height;Sex;Favourite colour;Diploma\n";

        m_clearButton->AddOnClickListener("Quit", [this](const Button& b)
        {
            Clear();
        });

        // Listener
        m_addPersonButton->AddOnClickListener("Add", [this](const Trema::View::Button &)
        {
            auto newId = ++m_count;
            std::stringstream ss;
            ss << newId;

            auto firstName = m_firstNameField->GetText();
            auto lastName = m_lastNameField->GetText();
            auto height = m_heightField->GetValue();
            auto sex = m_sexField->GetOption();
            auto favouriteColour = m_favouriteColourField->GetColorInt() | 0xFF; // Full blast alpha!
            auto diploma = m_diplomaField->GetOption();

            auto row = TableRow::CreateTableRow(m_peopleGrid, ss.str());
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

            m_data << firstName << ";"
                 << lastName << ";"
                 << std::dec << height << " cm;"
                 << sex << ";"
                 << std::hex << favouriteColour << ";"
                 << diploma << "\n";

            m_peopleGrid->AddValue(row);
            Clear();
        });

        m_quitOption->AddOnClickListener("Quit", [this](const MenuOption &)
        {
            QuitApplication();
        });

        m_disconnectOption->AddOnClickListener("Disconnect", [this](const MenuOption&)
        {
            Intent intent;
            intent.SetStringExtra("test", "SALUT LES BENZ");
            QuitActivity(200, intent);
        });

        m_saveOption->AddOnClickListener("Save", [this, &data](const Trema::View::MenuOption &)
        {
            GetComponent<FileDialog>()->ShowFileDialog("./", ".csv", [&data](const std::string &path)
            {
                std::stringstream filePath;
                filePath << path;

                if(path.find(".csv", path.length() - 5) == std::string::npos)
                    filePath << ".csv";

                std::ofstream output(filePath.str());
                output << data.str();
            }, Trema::View::SaveFile);
        });
    }

private:
    int m_count = 0;
    std::shared_ptr<TextInput> m_firstNameField;
    std::shared_ptr<TextInput> m_lastNameField;
    std::shared_ptr<SliderInt> m_heightField;
    std::shared_ptr<Radio> m_sexField;
    std::shared_ptr<ColorPicker> m_favouriteColourField;
    std::shared_ptr<Combo> m_diplomaField;

    // Buttons & Table
    std::shared_ptr<Table> m_peopleGrid;
    std::shared_ptr<Button> m_addPersonButton;
    std::shared_ptr<Button> m_clearButton;

    // Menu
    std::shared_ptr<MenuOption> m_disconnectOption;
    std::shared_ptr<MenuOption> m_quitOption;
    std::shared_ptr<MenuOption> m_saveOption;

    // Data
    std::stringstream m_data;

    void Clear()
    {
        m_firstNameField->SetText("");
        m_lastNameField->SetText("");
        m_heightField->SetValue(50);
        m_sexField->SetOption(0);
        m_diplomaField->SetOption("");
    }
};

class LoginActivity : public Activity
{
public:
    LoginActivity(Intent intent, uint16_t requestCode = -1) :
        Activity(std::move(intent), requestCode)
    {

    }

    void OnCreateView() override
    {
        LoadView("./resources/views/login_view.txml");
    }

    void OnActivityStart() override
    {
        m_mailAddress = GetElementById<TextInput>("mailAddress");
        m_loginButton = GetElementById<Button>("loginButton");
        m_loginButton->AddOnClickListener("Login", [this](const Button &)
        {
            StartActivity<PeopleActivity>();
            // m_collection->GetContainer().emplace_back("test");
        });

        auto container = GetElementById<WindowContainer>("credentials");
        std::vector<std::string> credentials = {"test", "test2", "test3"};
        m_collection = std::make_shared<ObservableCollection<std::vector<std::string>>>(credentials);
        auto vectorView = VectorView::CreateVectorView(container, "credentials", m_collection);
        container->AddChild(vectorView);
    }

    void OnActivityResult(uint16_t requestCode, uint16_t resultCode, Intent intent) override
    {
        m_mailAddress->SetText(intent.GetStringExtra("test"));
    }

    void OnActivityUpdate(double deltaTime) override
    {
        /*const auto fmt = u8"DeltaTime: {}";
        std::cout << std::format(fmt, deltaTime) << std::endl;*/
    }

private:
    std::shared_ptr<Button> m_loginButton;
    std::shared_ptr<TextInput> m_mailAddress;
    std::shared_ptr<ObservableCollection<std::vector<std::string>>> m_collection;
};

int Main(const std::vector<std::string>& args)
{
    WindowBuilder<GLFWWindow>().
            WithActivity(ActivityBuilder<LoginActivity>().CreateActivity(Intent())).
            WithPopupComponent<FileDialog>(FileDialog::CreateFileDialog("Export...")).
            WithErrorsOutput(true).
            Build()->
            Run();

    return EXIT_SUCCESS;
}
