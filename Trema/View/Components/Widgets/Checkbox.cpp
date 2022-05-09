//
// Created by JajaFil on 2/15/2022.
//

#include <future>
#include "Checkbox.h"
#include "../../ImGUI/imgui.h"

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
        EndStyle();
    }

    std::shared_ptr<Checkbox> Checkbox::CreateCheckbox(std::shared_ptr<GuiElement> parent, std::string name)
    {
        return std::make_shared<Checkbox>(std::move(parent), std::move(name));
    }
}