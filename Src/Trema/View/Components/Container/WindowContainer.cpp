//
// Created by JajaFil on 2/13/2022.
//

#include "WindowContainer.h"
#include <imgui.h>
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

    void WindowContainer::AlignX()
    {
        auto size = GetSize();
        auto windowSize = ImGui::GetWindowSize();

        if(Style.GetHorizontalAlignment() == Center)
        {
            ImGui::SetCursorPosX((windowSize.x / 2) - (size.x / 2));
        }
        else if(Style.GetHorizontalAlignment() == End)
        {
            ImGui::SetCursorPosX(windowSize.x - size.x);
        }
    }

    void WindowContainer::AlignY()
    {
        auto size = GetSize();
        auto windowSize = ImGui::GetWindowSize();

        if(Style.GetVerticalAlignment() == Center)
        {
            ImGui::SetCursorPosY((windowSize.y / 2) - (size.y / 2));
        }
        else if(Style.GetVerticalAlignment() == End)
        {
            ImGui::SetCursorPosY(windowSize.y - size.y);
        }
    }

    void WindowContainer::ShowPureWindow()
    {
        ImGui::Begin(NameId(), m_closable ? &m_isOpened : nullptr, GetWindowFlags());

        ImVec2 size = { 0, 0 };
        bool horizontal = (Style.GetOrientation() == Row);
        bool notFirst = false;

        AlignY();

        for(const auto& element : m_children)
        {
            AlignX();
            element->PreShow();
            if(!notFirst)
                notFirst = true;
            else if(horizontal)
                ImGui::SameLine();

            element->Show();
            UpdateSize(size, horizontal, element);
        }

        m_layoutSize = size;
        ImGui::End();
    }

    void WindowContainer::ShowSubContainer()
    {
        bool horizontal = (Style.GetOrientation() == Row);
        bool notFirst = false;
        ImVec2 size = { 0, 0 };

        AlignY();

        for(const auto& element : m_children)
        {
            AlignX();
            element->PreShow();
            if(!notFirst)
                notFirst = true;
            else if(horizontal)
                ImGui::SameLine();

            element->Show();
            UpdateSize(size, horizontal, element);
        }

        m_layoutSize = size;
    }

    void WindowContainer::UpdateSize(ImVec2& size, bool horizontal, const std::shared_ptr<GuiElement>& element) const
    {
        auto windowSize = ImGui::GetWindowSize();
        auto padding = Style.GetWindowPadding();
        if(horizontal)
        {
            auto elementSize = element->GetLayoutSize().y;
            size.x += element->GetLayoutSize().x;
            size.y = std::max(size.y, elementSize);
        }
        else
        {
            auto elementSize = element->GetLayoutSize().x;
            size.x = std::max(size.x, elementSize);
            size.y += element->GetLayoutSize().y;
        }

        size.x = std::min(size.x, windowSize.x - padding.x * 2);
        size.y = std::min(size.y, windowSize.y - padding.y * 2);
    }

    int WindowContainer::GetWindowFlags()
    {
        int flags = ImGuiWindowFlags_None;

        if(!Style.GetWindowHeaderVisibility())
            flags |= ImGuiWindowFlags_NoTitleBar;

        return flags;
    }
}