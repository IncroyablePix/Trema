//
// Created by JajaFil on 4/17/2022.
//

#include "StyleColor.h"

namespace Trema::View
{
    void StyleColor::SetColor(int color)
    {
        SetColor(*((unsigned int*) &color));
    }

    void StyleColor::SetColor(unsigned int color)
    {
        SetColor({
                             (float) ((color >> 24) & 0xFF) / 255.0f,
                             (float) ((color >> 16) & 0xFF) / 255.0f,
                             (float) ((color >> 8) & 0xFF) / 255.0f,
                             (float) ((color) & 0xFF) / 255.0f
                     });
    }

    void StyleColor::SetColor(const ImVec4 &color)
    {
        m_hasColor = true;
        m_color = color;
    }

    ImVec4 StyleColor::GetColor() const
    {
        return m_color;
    }

    bool StyleColor::HasColor() const
    {
        return m_hasColor;
    }
}