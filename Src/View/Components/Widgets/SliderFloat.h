//
// Created by JajaFil on 4/4/2022.
//

#ifndef TREMA_SLIDERFLOAT_H
#define TREMA_SLIDERFLOAT_H


#include <functional>
#include "../IGuiElement.h"

namespace Trema::View
{
    class SliderFloat : public IGuiElement
    {
    public:
        SliderFloat(std::shared_ptr<IGuiElement> parent, std::string name, float min, float max);
        ~SliderFloat() = default;
        void AddOnCheckListener(std::string name, std::function<void(const SliderFloat& slider, float value)> listener);
        void Show() override;

        static std::shared_ptr<SliderFloat> CreateSliderFloat(std::shared_ptr<IGuiElement> parent, std::string name, float min = 0.0f, float max = 100.0f);

    private:
        float m_value { 0.0f };
        float m_min { 0.0f };
        float m_max { 100.0f };
        std::unordered_map<std::string, std::function<void(const SliderFloat& slider, float value)>> m_listeners;
    };
}

#endif //TREMA_SLIDERFLOAT_H
