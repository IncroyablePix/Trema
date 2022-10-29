//
// Created by JajaFil on 4/22/2022.
//

#ifndef TREMA_SAMPLE_COLORPICKER_H
#define TREMA_SAMPLE_COLORPICKER_H

#include "../GuiElement.h"
#include <array>

namespace Trema::View
{
    class ColorPicker : public GuiElement
    {
    public:
        ColorPicker(std::shared_ptr<GuiElement> parent, std::string name);
        ColorPicker(const ColorPicker&) = delete;
        ColorPicker& operator=(const ColorPicker&) = delete;
        ~ColorPicker() override = default;

        void Show() override;
        void BeginStyle() override;
        void EndStyle() override;

        std::array<float, 4> GetColor() const;
        unsigned int GetColorInt() const;
        void AddOnChangeListener(std::string name, std::function<void(const ColorPicker& colorPicker)> listener);
        static std::shared_ptr<ColorPicker> CreateColorPicker(std::shared_ptr<GuiElement> parent, std::string name);

        inline bool HasPreview() const { return m_preview; }
        inline void TogglePreview(bool toggle) { m_preview = toggle; }
        inline bool HasInput() const { return m_hasInput; }
        inline void ToggleInput(bool toggle) { m_hasInput = toggle; }

        int GetFlags() const;

    private:
        std::array<float, 4> m_crossHairColor = { 0.0f, 0.0f, 0.0f, 0.0f };
        std::unordered_map<std::string, std::function<void(const ColorPicker& colorPicker)>> m_listeners;

        bool m_preview { false };
        bool m_hasInput { false };

        void UpdateSize();
    };
}

#endif //TREMA_SAMPLE_COLORPICKER_H
