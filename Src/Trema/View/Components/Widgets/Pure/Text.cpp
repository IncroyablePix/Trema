//
// Created by JajaFil on 2/15/2022.
//

#include "Text.h"
#include <imgui.h>

#include <utility>

namespace Trema::View
{

    Text::Text(std::shared_ptr<GuiElement> parent, std::string name, bool wrapped) :
            GuiElement(std::move(parent), std::move(name)),
            m_wrapped(wrapped)
    {

    }

    Text::~Text() = default;

    void Text::Show()
    {
        BeginStyle();

        AlignX();

        if(m_wrapped)
            ImGui::TextWrapped("%s", NameId());
        else
            ImGui::Text("%s", NameId());

        UpdateSize();
        EndStyle();
    }

    void Text::UpdateSize()
    {
        const auto width = ImGui::CalcTextSize(NameId()).x;
        const auto height = ImGui::CalcTextSize(NameId()).y;
        m_layoutSize = { width, height };
    }

    const std::string &Text::GetName()
    {
        return m_name;
    }

    std::shared_ptr<Text> Text::CreateText(std::shared_ptr<GuiElement> parent, std::string name, bool wrapped)
    {
        return std::make_shared<Text>(std::move(parent), std::move(name), wrapped);
    }

    void Text::SetWrapped(bool wrapped)
    {
        m_wrapped = wrapped;
    }

    bool Text::GetWrapped() const
    {
        return m_wrapped;
    }
}