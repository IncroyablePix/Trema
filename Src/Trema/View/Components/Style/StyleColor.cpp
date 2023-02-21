#include "StyleColor.h"

namespace Trema::View
{
    StyleColor::StyleColor() :
            m_color({ 1.0f, 1.0f, 1.0f, 1.0f })
    {

    }

    StyleColor::StyleColor(ImVec4 color) :
            m_color(color)
    {
        m_hasColor = true;
    }

    void StyleColor::SetColor(int color)
    {
        SetColor(*((unsigned int*) &color));
    }

    void StyleColor::SetColor(unsigned int color)
    {
        SetColor(
        {
            (float) ((color >> 24) & 0xFF) / 255.0f,
            (float) ((color >> 16) & 0xFF) / 255.0f,
            (float) ((color >> 8) & 0xFF) / 255.0f,
            (float) (color & 0xFF) / 255.0f
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