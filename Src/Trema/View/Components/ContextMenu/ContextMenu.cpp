//
// Created by JajaFil on 7/22/2022.
//

#include "ContextMenu.h"

namespace Trema::View
{

    ContextMenu::ContextMenu(std::shared_ptr<GuiElement> parent, std::string name) :
        Container(std::move(parent), std::move(name))
    {

    }

    void ContextMenu::Show()
    {
        BeginStyle();

        if(ImGui::BeginPopupContextItem(NameId(), ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_MouseButtonMiddle))
        {
            for(const auto& element : m_children)
            {
                element->Show();
            }

            ImGui::EndPopup();
        }

        EndStyle();
    }

}
