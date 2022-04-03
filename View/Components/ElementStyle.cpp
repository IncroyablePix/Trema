//
// Created by JajaFil on 3/6/2022.
//

#include <algorithm>
#include <regex>
#include "ElementStyle.h"
#include "../Utils/StringExtensions.h"

namespace Trema::View
{
    void ElementStyle::SetOrientation(enum Orientation orientation)
    {
        m_orientation = orientation;
    }

    void ElementStyle::SetOrientation(const std::string &orientation)
    {
        SetOrientation(orientation == "column" ? Column : Row);
    }

    enum Orientation ElementStyle::GetOrientation() const
    {
        return m_orientation;
    }

    void ElementStyle::SetAlpha(float alpha)
    {
        m_alpha = std::clamp(alpha, 0.f, 1.f);
    }

    void ElementStyle::SetAlpha(const std::string &alpha)
    {
        if(IsFloat(alpha))
        {
            m_alpha = std::stof(alpha);
        }
    }

    float ElementStyle::GetAlpha() const
    {
        return m_alpha;
    }

    void ElementStyle::SetTextColor(int color)
    {
        m_hasTextColor = true;
        m_textColor =
                {
                        (float) ((color >> 24) & 0xFF) / 255.0f,
                        (float) ((color >> 16) & 0xFF) / 255.0f,
                        (float) ((color >> 8) & 0xFF) / 255.0f,
                        (float) ((color) & 0xFF) / 255.0f
                };
    }

    /// Sets the color for text
    ///
    /// \param color ARGB Color
    void ElementStyle::SetTextColor(unsigned int color)
    {
        m_hasTextColor = true;

        m_textColor =
        {
            (float) ((color >> 24) & 0xFF) / 255.0f,
            (float) ((color >> 16) & 0xFF) / 255.0f,
            (float) ((color >> 8) & 0xFF) / 255.0f,
            (float) ((color) & 0xFF) / 255.0f
        };
    }

    /// Sets the color for text
    ///
    /// \param color ARGB Color
    void ElementStyle::SetTextColor(const ImVec4 &color)
    {
        m_hasTextColor = true;
        m_textColor = color;
    }

    void ElementStyle::SetTextColor(const std::string &color)
    {
        m_hasTextColor = true;

    }

    ImVec4 ElementStyle::GetTextColor() const
    {
        return m_textColor;
    }

    bool ElementStyle::HasTextColor() const
    {
        return m_hasTextColor;
    }

    void ElementStyle::SetWidth(std::string width)
    {
        m_width = std::move(width);
    }

    void ElementStyle::SetHeight(std::string height)
    {
        m_height = std::move(height);
    }

    ImVec2 ElementStyle::GetSize() const
    {
        float w = 0.0f, h = 0.0f;
        auto available = ImGui::GetContentRegionAvail();

        if(GetFromWord(m_width, w)) { }
        else if(GetFromPercents(m_width, w)) { }

        if(GetFromWord(m_height, h)) { }
        if(GetFromPercents(m_height, h))
        { }


        return { available.x * w, available.y * h };
    }

    bool ElementStyle::GetFromPercents(const std::string& value, float& floatValue)
    {
        if(std::regex_match(value, std::regex(R"(^-?\d*(\.\d+)?%$)")))
        {
            floatValue = strtof(value.c_str(), nullptr) / 100.0f;
            return true;
        }

        return false;
    }

    bool ElementStyle::GetFromWord(const std::string &value, float &floatValue)
    {
        if(value == "auto")
        {
            floatValue = 0.0f;
            return true;
        }

        return false;
    }


}