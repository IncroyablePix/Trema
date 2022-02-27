//
// Created by JajaFil on 2/13/2022.
//

#include "WindowContainer.h"
#include "../../ImGUI/imgui.h"

#include <utility>

namespace Trema::View
{
    WindowContainer::WindowContainer(std::shared_ptr<IGuiElement> parent, std::string name) :
        IContainer(std::move(parent), std::move(name))
    {

    }

    WindowContainer::~WindowContainer()
    {

    }

    void WindowContainer::Show()
    {
        ImGui::Begin(NameId());

        for(const auto& element : m_children)
        {
            element->Show();
        }

        ImGui::End();
    }

    std::shared_ptr<WindowContainer>
    WindowContainer::CreateWindowContainer(std::shared_ptr<IGuiElement> parent, std::string name)
    {
        return std::make_shared<WindowContainer>(std::move(parent), std::move(name));
    }
}