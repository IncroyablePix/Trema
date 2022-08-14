//
// Created by JajaFil on 2/13/2022.
//

#include "WindowContainer.h"
#include "../../ImGUI/imgui.h"

#include <utility>
#include <iostream>

namespace Trema::View
{
    WindowContainer::WindowContainer(std::shared_ptr<GuiElement> parent, std::string name) :
            Container(std::move(parent), std::move(name))
    {

    }

    WindowContainer::~WindowContainer() = default;

    void WindowContainer::Show()
    {
        BeginStyle();
        if(!Container::SubContainer)
        {
            Container::SubContainer = true;

            ShowPureWindow();

            Container::SubContainer = false;
        }
        else
        {
            ShowSubContainer();
        }

        EndStyle();
    }

    std::shared_ptr<WindowContainer>
    WindowContainer::CreateWindowContainer(std::shared_ptr<GuiElement> parent, std::string name)
    {
        return std::make_shared<WindowContainer>(std::move(parent), std::move(name));
    }

    void WindowContainer::ShowPureWindow()
    {
        ImGui::Begin(NameId(), m_closable ? &m_isOpened : nullptr, GetWindowFlags());

        ImVec2 size = { 0, 0 };
        bool horizontal = (Style.GetOrientation() == Row);
        bool notFirst = false;

        for(const auto& element : m_children)
        {
            if(!notFirst)
                notFirst = true;
            else if(horizontal)
                ImGui::SameLine();

            element->Show();
            UpdateSize(size, horizontal, element);
        }

        m_layoutSize = size;
        std::cout << m_layoutSize.x << ", " << m_layoutSize.y << std::endl;
        ImGui::End();
    }

    void WindowContainer::ShowSubContainer()
    {
        bool horizontal = (Style.GetOrientation() == Row);
        bool notFirst = false;
        ImVec2 size = { 0, 0 };

        for(const auto& element : m_children)
        {
            if(!notFirst)
                notFirst = true;
            else if(horizontal)
                ImGui::SameLine();

            element->Show();
            UpdateSize(size, horizontal, element);
        }

        m_layoutSize = size;
        std::cout << m_layoutSize.x << ", " << m_layoutSize.y << std::endl;
    }

    void WindowContainer::UpdateSize(ImVec2& size, bool horizontal, const std::shared_ptr<GuiElement>& element) const
    {
        if(horizontal)
        {
            size.x += element->GetLayoutSize().x;
            size.y = std::max(size.y, element->GetLayoutSize().y);
        }
        else
        {
            size.x = std::max(size.x, element->GetLayoutSize().x);
            size.y += element->GetLayoutSize().y;
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