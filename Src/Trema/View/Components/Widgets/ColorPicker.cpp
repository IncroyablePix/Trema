//
// Created by JajaFil on 4/22/2022.
//

#include "ColorPicker.h"

#include <utility>
#include <future>

namespace Trema::View
{

    ColorPicker::ColorPicker(std::shared_ptr<GuiElement> parent, std::string name) :
            GuiElement(std::move(parent), std::move(name))
    {

    }

    void ColorPicker::Show()
    {
        BeginStyle();
        AlignX();
        if(ImGui::ColorPicker4(NameId(), m_crossHairColor.data(), GetFlags()))
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

    void ColorPicker::BeginStyle()
    {
        GuiElement::BeginStyle();

        auto size = Style.GetSize();
        ImGui::SetNextItemWidth(size.x);
    }

    void ColorPicker::EndStyle()
    {
        GuiElement::EndStyle();
    }

    void ColorPicker::AddOnChangeListener(std::string name, std::function<void(const ColorPicker &)> listener)
    {
        m_listeners[std::move(name)] = std::move(listener);
    }

    std::shared_ptr<ColorPicker> ColorPicker::CreateColorPicker(std::shared_ptr<GuiElement> parent, std::string name)
    {
        return std::make_shared<ColorPicker>(std::move(parent), std::move(name));
    }

    std::array<float, 4> ColorPicker::GetColor() const
    {
        return m_crossHairColor;
    }

    unsigned int ColorPicker::GetColorInt() const
    {
        unsigned int color =
            ((int)(m_crossHairColor[0] * 255)) << 24 |
            ((int)(m_crossHairColor[1] * 255) << 16) |
            ((int)(m_crossHairColor[2] * 255) << 8) |
            ((int)(m_crossHairColor[3] * 255));

        return color;
    }

    int ColorPicker::GetFlags() const
    {
        int flags = ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoOptions;

        if(!m_preview)
            flags |= ImGuiColorEditFlags_NoSidePreview;

        if(!m_hasInput)
            flags |= ImGuiColorEditFlags_NoInputs;

        return flags;
    }

    void ColorPicker::UpdateSize()
    {
        const auto height = ImGui::GetItemRectSize().y;
        const auto width = ImGui::GetItemRectSize().x;
        m_layoutSize = { width, height };
    }
}