//
// Created by JajaFil on 3/6/2022.
//

#include <algorithm>
#include <regex>
#include "ElementStyle.h"
#include "../../Utils/StringExtensions.h"

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
        float w = -0.0f, h = -0.0f;
        auto available = ImGui::GetContentRegionAvail();

        if(GetFromWord(m_width, w)) { }
        else if(GetFromPercents(m_width, w)) { w *= available.x; }
        else if(GetFromPx(m_width, w)) { }

        if(GetFromWord(m_height, h)) { }
        else if(GetFromPercents(m_height, h)) { h *= available.y; }
        else if(GetFromPx(m_height, h)) { }

        return { w, h };
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

    bool ElementStyle::GetFromPx(const std::string& value, float& floatValue)
    {
        if(std::regex_match(value, std::regex(R"(^\d+px$)")))
        {
            floatValue = strtof(value.c_str(), nullptr);
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

    void ElementStyle::SetWindowPaddingX(float x)
    {
        m_windowPadding.x = x;
    }

    void ElementStyle::SetWindowPaddingY(float y)
    {
        m_windowPadding.y = y;
    }

    void ElementStyle::SetWindowPadding(float x, float y)
    {
        m_windowPadding.x = x;
        m_windowPadding.y = y;
    }

    void ElementStyle::SetWindowPadding(ImVec2 padding)
    {
        m_windowPadding = padding;
    }

    ImVec2 ElementStyle::GetWindowPadding() const
    {
        return m_windowPadding;
    }

    void ElementStyle::SetFramePaddingX(float x)
    {
        m_framePadding.x = x;
    }

    void ElementStyle::SetFramePaddingY(float y)
    {
        m_framePadding.y = y;
    }

    void ElementStyle::SetFramePadding(float x, float y)
    {
        m_framePadding.x = x;
        m_framePadding.y = y;
    }

    void ElementStyle::SetFramePadding(ImVec2 padding)
    {
        m_framePadding = padding;
    }

    ImVec2 ElementStyle::GetFramePadding() const
    {
        return m_framePadding;
    }

    void ElementStyle::SetFrameRounding(float rounding)
    {
        m_frameRounding = rounding;
    }

    float ElementStyle::GetFrameRounding() const
    {
        return m_frameRounding;
    }

    void ElementStyle::SetWindowRounding(float rounding)
    {
        m_windowRounding = rounding;
    }

    float ElementStyle::GetWindowRounding() const
    {
        return m_windowRounding;
    }

    void ElementStyle::SetFont(std::string fontName)
    {
        m_font = std::move(fontName);
    }

    std::string &ElementStyle::GetFont()
    {
        return m_font;
    }

    void ElementStyle::SetWindowHeaderVisibility(bool toggle)
    {
        m_windowHeader = toggle;
    }

    bool ElementStyle::GetWindowHeaderVisibility() const
    {
        return m_windowHeader;
    }
}