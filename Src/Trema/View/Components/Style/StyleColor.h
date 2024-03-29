#ifndef TREMA_STYLECOLOR_H
#define TREMA_STYLECOLOR_H

#include <imgui.h>

namespace Trema::View
{
    class StyleColor
    {
    private:
        ImVec4 m_color = {1.0f, 1.0f, 1.0f, 1.0f};
        bool m_hasColor {false};

    public:
        StyleColor();
        StyleColor(ImVec4 color);
        void SetColor(int color);
        void SetColor(unsigned int color);
        void SetColor(const ImVec4 &color);
        ImVec4 GetColor() const;
        bool HasColor() const;
    };
}

#endif //TREMA_STYLECOLOR_H
