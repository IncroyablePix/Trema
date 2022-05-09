//
// Created by JajaFil on 2/16/2022.
//

#include "GuiElement.h"
#include "../ImGUI/imgui.h"
#include "../Windowing/Fonts/FontsRepository.h"

#include <utility>

namespace Trema::View
{
    GuiElement::GuiElement(std::shared_ptr<GuiElement> parent, std::string name) :
        m_parent(std::move(parent)),
        m_name(std::move(name)),
        m_styles(0),
        m_colors(0)
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

    const char *GuiElement::NameId()
    {
        return m_name.c_str();
    }

    void GuiElement::BeginStyle()
    {
        auto size = Style.GetSize();

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

        if(!Style.GetFont().empty() && m_fontName != Style.GetFont())
            m_font = (*FontsRepository::GetInstance())[m_fontName = Style.GetFont()].Font;

        if(m_font)
            ImGui::PushFont(m_font);
    }

    void GuiElement::EndStyle()
    {
        ImGui::PopStyleVar((int) m_styles);
        m_styles = 0;

        ImGui::PopStyleColor((int) m_colors);
        m_colors = 0;

        if(m_font)
            ImGui::PopFont();
    }

    ImVec2 GuiElement::GetItemSize() const
    {
        return Style.GetSize();
    }
}