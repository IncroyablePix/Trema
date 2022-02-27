//
// Created by JajaFil on 2/13/2022.
//

#include "TopMenu.h"
#include "../../ImGUI/imgui.h"

namespace Trema::View
{
    TopMenu::TopMenu(std::string name) :
    IGuiElement(nullptr, std::move(name))
    {

    }

    TopMenu::~TopMenu()
    {

    }

    void TopMenu::Show()
    {
        if(ImGui::BeginMainMenuBar())
        {
        }
        ImGui::EndMainMenuBar();
    }

    std::shared_ptr<TopMenu> TopMenu::CreateTopMenu(std::string name)
    {
        return std::make_shared<TopMenu>(std::move(name));
    }
}