//
// Created by JajaFil on 2/16/2022.
//

#include "GuiElement.h"
#include <imgui.h>
#include "../Windowing/Fonts/FontsRepository.h"

#include <utility>

namespace Trema::View
{
    GuiElement::GuiElement(std::shared_ptr<GuiElement> parent, std::string name) :
        m_parent(std::move(parent)),
        m_name(std::move(name))
    {

    }

    const std::string &GuiElement::GetName()
    {
        return m_name;
    }

    void GuiElement::SetName(std::string name)
    {
        m_name = std::move(name);
    }

    const char *GuiElement::NameId() const
    {
        return m_name.c_str();
    }

    void GuiElement::BeginStyle()
    {
        auto size = Style.GetSize();

        if(!m_isWindow)
        {
            auto margin = Style.GetMargin();

            if(margin.x != 0.0)
            {
                ImGui::Dummy({margin.w, margin.x });

            }
            if(margin.w != 0.0)
            {
                ImGui::Dummy({margin.w, 0.0f });
                ImGui::SameLine();
            }
        }

        if(Style.GetAlpha() > 0)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, Style.GetAlpha());
            m_styles++;
        }

        if(size.x != 0.0f)
            ImGui::SetNextItemWidth(size.x);

        if(Style.TextColor().HasColor())
        {
            ImGui::PushStyleColor(ImGuiCol_Text, Style.TextColor().GetColor());
            m_colors++;
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, Style.GetWindowPadding());
        m_styles++;

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, Style.GetFramePadding());
        m_styles++;

        if(!Style.GetFont().empty() && m_fontName != Style.GetFont())
            m_font = (*FontsRepository::GetInstance())[m_fontName = Style.GetFont()].Font;

        if(m_font)
            ImGui::PushFont(m_font);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, Style.GetWindowPadding());
        m_styles ++;
    }

    void GuiElement::EndStyle()
    {
        ImGui::PopStyleVar((int) m_styles);
        m_styles = 0;

        ImGui::PopStyleColor((int) m_colors);
        m_colors = 0;

        if(m_font)
            ImGui::PopFont();


        if(!m_isWindow)
        {
            auto margin = Style.GetMargin();

            if(margin.y != 0.0 || margin.z != 0.0)
            {
                ImGui::SameLine();
                ImGui::Dummy({margin.y, margin.z});
            }
        }
    }

    ImVec2 GuiElement::GetItemSize() const
    {
        return Style.GetSize();
    }

    /*void GuiElement::ShowContextMenu()
    {
        if(m_contextMenu)
        {
            ImGui::OpenPopup(m_contextMenu->NameId());
        }
    }*/

    void GuiElement::PollEvents()
    {
        if(ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
        {
            ImGui::OpenPopup(m_contextMenu.c_str());
        }
    }

    ImVec2 GuiElement::GetSize() const
    {
        auto size = Style.GetSize();

        auto width = std::min(m_layoutSize.x, size.x);
        if(width == 0)
            width = std::max(m_layoutSize.x, size.x);

        auto height = std::min(m_layoutSize.y, size.y);
        if(height == 0)
            height = std::max(m_layoutSize.y, size.y);

        if(m_parent)
        {
            auto parentSize = m_parent->GetLayoutSize();
            if(parentSize.x != 0)
                width = width == 0 ?
                        std::max(width, parentSize.x) :
                        std::min(width, parentSize.x);

            if(parentSize.y != 0)
                height = height == 0 ?
                        std::max(height, parentSize.y) :
                        std::min(height, parentSize.y);
        }

        if(size.x != 0)
            width = std::min(width, size.x);

        if(size.y != 0)
            height = std::min(height, size.y);

        return { width, height };
    }

    void GuiElement::PreShow()
    {
        auto size = GetSize();
        if(size.x != 0.0f)
            ImGui::PushItemWidth(size.x);
    }

    void GuiElement::AlignX()
    {
        ImVec2 containerSize = m_parent ? m_parent->GetLayoutSize() : ImGui::GetContentRegionAvail();
        auto size = GetSize();

        if(Style.GetHorizontalAlignment() == Center)
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (containerSize.x / 2) - (size.x / 2));
        }
        else if(Style.GetHorizontalAlignment() == End)
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + containerSize.x - size.x);
        }
    }

    void GuiElement::AlignY()
    {
        // TODO : Tomorrow
    }
}