//
// Created by JajaFil on 27/04/22.
//

#ifndef TREMA_PROJECT_SLIDERINT_H
#define TREMA_PROJECT_SLIDERINT_H

#include "../../GuiElement.h"

namespace Trema::View
{
    class SliderInt : public GuiElement
    {
    public:
        SliderInt(std::shared_ptr<GuiElement> parent, std::string name, int min, int max);
        SliderInt(const SliderInt&) = delete;
        SliderInt& operator=(const SliderInt&) = delete;
        ~SliderInt() = default;
        void AddOnCheckListener(std::string name, std::function<void(const SliderInt& slider, int value)> listener);
        void Show() override;

        inline void SetMin(int min) { m_min = min; m_value = std::clamp<int>(m_value, m_min, m_max); }
        inline void SetMax(int max) { m_max = max; m_value = std::clamp<int>(m_value, m_min, m_max); }
        void SetValue(int value);

        inline int GetValue() const { return m_value; }

        static std::shared_ptr<SliderInt> CreateSliderInt(std::shared_ptr<GuiElement> parent, std::string name, int min = 0.0f, int max = 100.0f);

    private:
        int m_value { 0 };
        int m_min { 0 };
        int m_max { 100 };
        std::unordered_map<std::string, std::function<void(const SliderInt& slider, int value)>> m_listeners;
    };
}

#endif //TREMA_PROJECT_SLIDERINT_H
