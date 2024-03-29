#ifndef TREMA_SLIDERFLOAT_H
#define TREMA_SLIDERFLOAT_H


#include <functional>
#include <algorithm>
#include "../../GuiElement.h"

namespace Trema::View
{
    class SliderFloat : public GuiElement
    {
    public:
        SliderFloat(std::shared_ptr<GuiElement> parent, std::string name, float min, float max);
        SliderFloat(const SliderFloat&) = delete;
        SliderFloat& operator=(const SliderFloat&) = delete;
        ~SliderFloat() override = default;
        void AddOnCheckListener(std::string name, std::function<void(const SliderFloat& slider, float value)> listener);
        void Show() override;

        inline void SetMin(float min) { m_min = min; m_value = std::clamp<float>(m_value, m_min, m_max); }
        inline void SetMax(float max) { m_max = max; m_value = std::clamp<float>(m_value, m_min, m_max); }

        inline float GetValue() const { return m_value; }

        static std::shared_ptr<SliderFloat> CreateSliderFloat(std::shared_ptr<GuiElement> parent, std::string name, float min = 0.0f, float max = 100.0f);

    private:
        float m_value { 0.0f };
        float m_min { 0.0f };
        float m_max { 100.0f };
        std::unordered_map<std::string, std::function<void(const SliderFloat& slider, float value)>> m_listeners;
    };
}

#endif //TREMA_SLIDERFLOAT_H
