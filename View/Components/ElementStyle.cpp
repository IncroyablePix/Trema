//
// Created by JajaFil on 3/6/2022.
//

#include <algorithm>
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
        SetOrientation(orientation == "Column" ? Column : Row);
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


}