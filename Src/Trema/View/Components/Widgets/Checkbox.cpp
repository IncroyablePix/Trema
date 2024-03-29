#include <future>
#include <iostream>
#include "Checkbox.h"
#include <imgui.h>

namespace Trema::View
{
    Checkbox::Checkbox(std::shared_ptr<GuiElement> parent, std::string name) :
            GuiElement(std::move(parent), std::move(name))
    {

    }

    Checkbox::~Checkbox()
    {

    }

    void Checkbox::AddOnCheckListener(std::string name, std::function<void(const Checkbox &, bool)> listener)
    {
        m_listeners[std::move(name)] = std::move(listener);
    }

    void Checkbox::Show()
    {
        BeginStyle();
        if(ImGui::Checkbox(m_name.c_str(), &m_checked))
        {
            auto future = std::async(std::launch::async, [this]()
            {
                for(const auto& [name, function] : m_listeners)
                {
                    function(*this, m_checked);
                }
            });
        }

        UpdateSize();
        EndStyle();
    }

    std::shared_ptr<Checkbox> Checkbox::CreateCheckbox(std::shared_ptr<GuiElement> parent, std::string name)
    {
        return std::make_shared<Checkbox>(std::move(parent), std::move(name));
    }

    void Checkbox::UpdateSize()
    {
        const auto height = ImGui::GetFrameHeightWithSpacing();
        const auto width = ImGui::GetFrameHeightWithSpacing() + ImGui::CalcTextSize(NameId()).x;
        m_layoutSize = { width, height };
    }
}