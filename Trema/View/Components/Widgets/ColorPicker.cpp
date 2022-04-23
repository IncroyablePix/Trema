//
// Created by JajaFil on 4/22/2022.
//

#include "ColorPicker.h"

#include <utility>
#include <future>

namespace Trema::View
{

    ColorPicker::ColorPicker(std::shared_ptr<IGuiElement> parent, std::string name) :
            IGuiElement(std::move(parent), std::move(name))
    {

    }

    void ColorPicker::Show()
    {
        BeginStyle();
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
        EndStyle();
    }

    void ColorPicker::BeginStyle()
    {
        IGuiElement::BeginStyle();

        auto size = Style.GetSize();
        ImGui::SetNextItemWidth(size.x);
    }

    void ColorPicker::EndStyle()
    {
        IGuiElement::EndStyle();
    }

    void ColorPicker::AddOnChangeListener(std::string name, std::function<void(const ColorPicker &)> listener)
    {
        m_listeners[std::move(name)] = std::move(listener);
    }

    std::shared_ptr<ColorPicker> ColorPicker::CreateColorPicker(std::shared_ptr<IGuiElement> parent, std::string name)
    {
        return std::make_shared<ColorPicker>(std::move(parent), std::move(name));
    }

    std::array<float, 4> ColorPicker::GetColor() const
    {
        return m_crossHairColor;
    }

    unsigned int ColorPicker::GetColorInt() const
    {
        return ImGui::ColorConvertFloat4ToU32({ m_crossHairColor[0], m_crossHairColor[1], m_crossHairColor[2], m_crossHairColor[3] });
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
}