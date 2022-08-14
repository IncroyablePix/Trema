//
// Created by JajaFil on 2/14/2022.
//

#include <future>
#include <iostream>
#include "Button.h"

namespace Trema::View
{

    Button::Button(std::shared_ptr<GuiElement> parent, std::string name) :
            GuiElement(std::move(parent), std::move(name))
    {

    }

    Button::~Button()
    {

    }

    void Button::AddOnClickListener(std::string name, std::function<void(const Button &)> function)
    {
        m_listeners[std::move(name)] = std::move(function);
    }

    void Button::Show()
    {
        BeginStyle();

        if(ImGui::Button(NameId(), GetItemSize()))
        {

            auto future = std::async(std::launch::async, [this]()
            {
                for(const auto& [name, function] : m_listeners)
                {
                    function(*this);
                }
            });
        }

        UpdateSize();
        EndStyle();
    }

    void Button::UpdateSize()
    {
        const auto height = ImGui::CalcTextSize(NameId()).y + ImGui::GetStyle().FramePadding.y * 2.0f;
        const auto width = ImGui::CalcTextSize(NameId()).x + ImGui::GetStyle().FramePadding.x * 2.0f;
        m_layoutSize = { width, height };
    }

    std::shared_ptr<Button> Button::CreateButton(std::shared_ptr<GuiElement> parent, std::string name)
    {
        return std::make_shared<Button>(std::move(parent), std::move(name));
    }
}