//
// Created by JajaFil on 4/4/2022.
//

#include <future>
#include "SliderFloat.h"

namespace Trema::View
{
    SliderFloat::SliderFloat(std::shared_ptr<GuiElement> parent, std::string name, float min = 0.0f, float max = 100.0f) :
            GuiElement(std::move(parent), std::move(name)),
            m_min(min),
            m_max(max)
    {
        m_value = std::clamp<float>(0.0, m_min, m_max);
    }

    void SliderFloat::AddOnCheckListener(std::string name, std::function<void(const SliderFloat& slider, float value)> listener)
    {
        m_listeners[std::move(name)] = std::move(listener);
    }

    void SliderFloat::Show()
    {
        BeginStyle();

        if(ImGui::SliderFloat(NameId(), &m_value, m_min, m_max))
        {
            auto future = std::async(std::launch::async, [this]()
            {
                for(const auto& [name, function] : m_listeners)
                {
                    function(*this, m_value);
                }
            });
        }

        EndStyle();
    }

    std::shared_ptr<SliderFloat>
    SliderFloat::CreateSliderFloat(std::shared_ptr<GuiElement> parent, std::string name, float min, float max)
    {
        return std::make_shared<SliderFloat>(std::move(parent), std::move(name), min, max);
    }
}