//
// Created by JajaFil on 27/04/22.
//

#include <future>
#include "SliderInt.h"

namespace Trema::View
{
    SliderInt::SliderInt(std::shared_ptr<GuiElement> parent, std::string name, int min = 0, int max = 100) :
            GuiElement(std::move(parent), std::move(name)),
            m_min(min),
            m_max(max)
    {
        m_value = std::clamp<int>(0.0, m_min, m_max);
    }

    void SliderInt::AddOnCheckListener(std::string name, std::function<void(const SliderInt& slider, int value)> listener)
    {
        m_listeners[std::move(name)] = std::move(listener);
    }

    void SliderInt::Show()
    {
        BeginStyle();

        if(ImGui::SliderInt(NameId(), &m_value, m_min, m_max))
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

    void SliderInt::SetValue(int value)
    {
        m_value = std::clamp<int>(value, m_min, m_max);
    }

    std::shared_ptr<SliderInt>
    SliderInt::CreateSliderInt(std::shared_ptr<GuiElement> parent, std::string name, int min, int max)
    {
        return std::make_shared<SliderInt>(std::move(parent), std::move(name), min, max);
    }
}