//
// Created by JajaFil on 2/13/2022.
//

#include "TopMenu.h"
#include "../../ImGUI/imgui.h"
#include "SubMenu.h"
#include "../Widgets/FamilyException.h"

namespace Trema::View
{
    TopMenu::TopMenu(std::string name) :
    IContainer(nullptr, std::move(name))
    {

    }

    TopMenu::~TopMenu()
    {

    }

    void TopMenu::Show()
    {
        if(ImGui::BeginMainMenuBar())
        {
            for(const auto& sub : m_children)
            {
                sub->Show();
            }
        }
        ImGui::EndMainMenuBar();
    }

    std::shared_ptr<TopMenu> TopMenu::CreateTopMenu(std::string name)
    {
        return std::make_shared<TopMenu>(std::move(name));
    }

    void TopMenu::AddChild(std::shared_ptr<GuiElement> child)
    {
        if(!IsType<SubMenu>(child))
            throw FamilyException(R"(Invalid type appended to "TopMenu", expected "SubMenu".)");

        IContainer::AddChild(child);
    }
}