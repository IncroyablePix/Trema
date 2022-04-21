//
// Created by JajaFil on 2/13/2022.
//

#include "WindowContainer.h"
#include "../../ImGUI/imgui.h"

#include <utility>
#include <iostream>

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
        BeginStyle();
        if(!IContainer::SubContainer)
        {
            IContainer::SubContainer = true;

            ShowPureWindow();

            IContainer::SubContainer = false;
        }
        else
        {
            ShowSubContainer();
        }
        EndStyle();
    }

    std::shared_ptr<WindowContainer>
    WindowContainer::CreateWindowContainer(std::shared_ptr<IGuiElement> parent, std::string name)
    {
        return std::make_shared<WindowContainer>(std::move(parent), std::move(name));
    }

    void WindowContainer::ShowPureWindow()
    {
        ImGui::Begin(NameId(), m_closable ? &m_isOpened : nullptr, GetWindowFlags());

        bool horizontal = (Style.GetOrientation() == Row);
        bool notFirst = false;

        for(const auto& element : m_children)
        {
            if(!notFirst)
                notFirst = true;
            else if(horizontal)
                ImGui::SameLine();

            element->Show();
        }

        ImGui::End();
    }

    void WindowContainer::ShowSubContainer()
    {
        bool horizontal = (Style.GetOrientation() == Row);
        bool notFirst = false;

        for(const auto& element : m_children)
        {
            if(!notFirst)
                notFirst = true;
            else if(horizontal)
                ImGui::SameLine();

            element->Show();
        }
    }

    int WindowContainer::GetWindowFlags()
    {
        int flags = ImGuiWindowFlags_None;

        if(!Style.GetWindowHeaderVisibility())
            flags |= ImGuiWindowFlags_NoTitleBar;

        return flags;
    }
}