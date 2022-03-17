//
// Created by JajaFil on 2/16/2022.
//

#include "IGuiElement.h"
#include "../ImGUI/imgui.h"

#include <utility>

namespace Trema::View
{
    IGuiElement::IGuiElement(std::shared_ptr<IGuiElement> parent, std::string name) :
        m_parent(std::move(parent)),
        m_name(std::move(name)),
        m_styles(0),
        m_colors(0)
    {

    }

    const std::string &IGuiElement::GetName()
    {
        return m_name;
    }

    void IGuiElement::SetName(std::string name)
    {
        m_name = std::move(name);
    }

    const char *IGuiElement::NameId()
    {
        return m_name.c_str();
    }

    void IGuiElement::BeginStyle()
    {
        if(Style.GetAlpha() > 0)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, Style.GetAlpha());
            m_styles++;
        }

        if(Style.HasTextColor())
        {
            ImGui::PushStyleColor(ImGuiCol_Text, Style.GetTextColor());
            m_colors++;
        }
    }

    void IGuiElement::EndStyle()
    {
        ImGui::PopStyleVar((int) m_styles);
        m_styles = 0;

        ImGui::PopStyleColor((int) m_colors);
        m_colors = 0;
    }
}