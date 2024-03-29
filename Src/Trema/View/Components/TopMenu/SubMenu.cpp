#include "SubMenu.h"
#include "MenuOption.h"
#include "../Widgets/FamilyException.h"
#include "../Widgets/Pure/Separator.h"

namespace Trema::View
{
    SubMenu::SubMenu(std::shared_ptr<GuiElement> parent, std::string name) :
            Container(std::move(parent), std::move(name))
    {

    }

    SubMenu::~SubMenu() = default;

    void SubMenu::Show()
    {
        if(ImGui::BeginMenu(NameId()))
        {
            for(const auto& opt : m_children)
                opt->Show();

            ImGui::EndMenu();
        }
    }

    std::shared_ptr<SubMenu> SubMenu::CreateSubMenu(std::shared_ptr<GuiElement> parent, std::string name)
    {
        return std::make_shared<SubMenu>(std::move(parent), std::move(name));
    }

    void SubMenu::AddChild(std::shared_ptr<GuiElement> child)
    {
        if(!IsType<MenuOption>(child) && !IsType<Separator>(child))
            throw FamilyException(R"(Invalid type appended to "SubMenu", expected "MenuOption", "Separator".)");

        Container::AddChild(child);
    }
}