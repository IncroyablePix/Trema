//
// Created by JajaFil on 4/17/2022.
//

#ifndef TREMA_STYLECOLOR_H
#define TREMA_STYLECOLOR_H

#include "../../ImGUI/imgui.h"

namespace Trema::View
{
    class StyleColor
    {
    private:
        ImVec4 m_color = {1.0f, 1.0f, 1.0f, 1.0f};
        bool m_hasColor {false};

    public:
        void SetColor(int color);
        void SetColor(unsigned int color);
        void SetColor(const ImVec4 &color);
        ImVec4 GetColor() const;
        bool HasColor() const;
    };
}

#endif //TREMA_STYLECOLOR_H
