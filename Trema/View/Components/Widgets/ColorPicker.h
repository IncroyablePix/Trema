//
// Created by JajaFil on 4/22/2022.
//

#ifndef TREMA_SAMPLE_COLORPICKER_H
#define TREMA_SAMPLE_COLORPICKER_H

#include "../IGuiElement.h"

namespace Trema::View
{
    class ColorPicker : public IGuiElement
    {
    public:
        ColorPicker(std::shared_ptr<IGuiElement> parent, std::string name);
        void Show() override;
        void BeginStyle() override;
        void EndStyle() override;

        std::array<float, 4> GetColor() const;
        unsigned int GetColorInt() const;
        void AddOnChangeListener(std::string name, std::function<void(const ColorPicker& colorPicker)> listener);
        static std::shared_ptr<ColorPicker> CreateColorPicker(std::shared_ptr<IGuiElement> parent, std::string name);

    private:
        std::array<float, 4> m_crossHairColor = { 0.0f, 0.0f, 0.0f, 0.0f };
        std::unordered_map<std::string, std::function<void(const ColorPicker& colorPicker)>> m_listeners;

    };
}

#endif //TREMA_SAMPLE_COLORPICKER_H
