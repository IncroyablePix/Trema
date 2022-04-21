//
// Created by JajaFil on 3/28/2022.
//

#include "SubMenu.h"
#include "MenuOption.h"
#include "../Widgets/FamilyException.h"
#include "../Widgets/Separator.h"

namespace Trema::View
{
    SubMenu::SubMenu(std::shared_ptr<IGuiElement> parent, std::string name) :
        IContainer(std::move(parent), std::move(name))
    {

    }

    SubMenu::~SubMenu()
    {

    }

    void SubMenu::Show()
    {
        if(ImGui::BeginMenu(NameId()))
        {
            for(const auto& opt : m_children)
                opt->Show();

            ImGui::EndMenu();
        }
    }

    std::shared_ptr<SubMenu> SubMenu::CreateSubMenu(std::shared_ptr<IGuiElement> parent, std::string name)
    {
        return std::make_shared<SubMenu>(std::move(parent), std::move(name));
    }

    void SubMenu::AddChild(std::shared_ptr<IGuiElement> child)
    {
        if(!IsType<MenuOption>(child) && !IsType<Separator>(child))
            throw FamilyException(R"(Invalid type appended to "SubMenu", expected "MenuOption", "Separator".)");

        IContainer::AddChild(child);
    }
}