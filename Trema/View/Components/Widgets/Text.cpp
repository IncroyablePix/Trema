//
// Created by JajaFil on 2/15/2022.
//

#include "Text.h"
#include "../../ImGUI/imgui.h"

#include <utility>

namespace Trema::View
{

    Text::Text(std::shared_ptr<IGuiElement> parent, std::string name, bool wrapped) :
            IGuiElement(std::move(parent), std::move(name)),
            m_wrapped(wrapped)
    {

    }

    Text::~Text()
    {

    }

    void Text::Show()
    {
        BeginStyle();

        if(m_wrapped)
            ImGui::TextWrapped("%s", NameId());
        else
            ImGui::Text("%s", NameId());

        EndStyle();
    }

    const std::string &Text::GetName()
    {
        return m_name;
    }

    std::shared_ptr<Text> Text::CreateText(std::shared_ptr<IGuiElement> parent, std::string name, bool wrapped)
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