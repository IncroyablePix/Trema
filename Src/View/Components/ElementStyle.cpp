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
            SetAlpha(std::stof(alpha));
        }
    }

    float ElementStyle::GetAlpha() const
    {
        return m_alpha;
    }

    void ElementStyle::SetTextColor(int color)
    {
        SetTextColor(*((unsigned int*) &color));
    }

    /// Sets the color for text
    ///
    /// \param color ARGB Color
    void ElementStyle::SetTextColor(unsigned int color)
    {
        SetTextColor({
            (float) ((color >> 24) & 0xFF) / 255.0f,
            (float) ((color >> 16) & 0xFF) / 255.0f,
            (float) ((color >> 8) & 0xFF) / 255.0f,
            (float) ((color) & 0xFF) / 255.0f
        });
    }

    /// Sets the color for text
    ///
    /// \param color ARGB Color
    void ElementStyle::SetTextColor(const ImVec4 &color)
    {
        m_hasTextColor = true;
        m_textColor = color;
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
        else if(GetFromPercents(m_height, h)) { }

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

    void ElementStyle::SetPaddingX(float x)
    {
        m_padding.x = x;
    }

    void ElementStyle::SetPaddingY(float y)
    {
        m_padding.y = y;
    }

    void ElementStyle::SetPadding(float x, float y)
    {
        m_padding.x = x;
        m_padding.y = y;
    }

    void ElementStyle::SetPadding(ImVec2 padding)
    {
        m_padding = padding;
    }

    ImVec2 ElementStyle::GetPadding() const
    {
        return m_padding;
    }

    void ElementStyle::SetRounding(float rounding)
    {
        m_rounding = rounding;
    }

    float ElementStyle::GetRounding() const
    {
        return m_rounding;
    }

    void ElementStyle::SetFont(std::string fontName)
    {
        m_font = std::move(fontName);
    }

    std::string &ElementStyle::GetFont()
    {
        return m_font;
    }

    /// Sets the color for text
    ///
    /// \param color ARGB Color
    void ElementStyle::SetBackgroundColor(unsigned int color)
    {
        SetBackgroundColor({
                (float) ((color >> 24) & 0xFF) / 255.0f,
                (float) ((color >> 16) & 0xFF) / 255.0f,
                (float) ((color >> 8) & 0xFF) / 255.0f,
                (float) ((color) & 0xFF) / 255.0f
        });
    }

    void ElementStyle::SetBackgroundColor(int color)
    {
        SetBackgroundColor(*((unsigned int*)&color));
    }

    /// Sets the color for text
    ///
    /// \param color ARGB Color
    void ElementStyle::SetBackgroundColor(const ImVec4 &color)
    {
        m_hasBackgroundColor = true;
        m_backgroundColor = color;
    }

    ImVec4 ElementStyle::GetBackgroundColor() const
    {
        return m_backgroundColor;
    }

    bool ElementStyle::HasBackgroundColor() const
    {
        return m_hasBackgroundColor;
    }

    void ElementStyle::SetHeaderColor(int color)
    {
        SetHeaderColor(*((unsigned int*)&color));
    }

    void ElementStyle::SetHeaderColor(unsigned int color)
    {
        SetHeaderColor({
       (float) ((color >> 24) & 0xFF) / 255.0f,
       (float) ((color >> 16) & 0xFF) / 255.0f,
       (float) ((color >> 8) & 0xFF) / 255.0f,
       (float) ((color) & 0xFF) / 255.0f
       });
    }

    void ElementStyle::SetHeaderColor(const ImVec4 &color)
    {
        m_hasHeaderColor = true;
        m_headerColor = color;
    }

    ImVec4 ElementStyle::GetHeaderColor() const
    {
        return m_headerColor;
    }

    bool ElementStyle::HasHeaderColor() const
    {
        return m_hasHeaderColor;
    }
}