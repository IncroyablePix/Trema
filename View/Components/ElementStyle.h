//
// Created by JajaFil on 3/6/2022.
//

#ifndef TREMA_ELEMENTSTYLE_H
#define TREMA_ELEMENTSTYLE_H

#include <string>
#include "../ImGUI/imgui.h"

namespace Trema::View
{
    enum Orientation
    {
        Column,
        Row
    };

    class ElementStyle
    {
    private:
        float m_alpha = -1.f;            // Transparency
        Orientation m_orientation = Row; // Orientation (radio buttons, ...)

        ImVec4 m_textColor = {1.0f, 1.0f, 1.0f, 1.0f };
        bool m_hasTextColor { false };

    public:
        void SetOrientation(enum Orientation orientation);
        void SetOrientation(const std::string &orientation);
        enum Orientation GetOrientation() const;

        void SetAlpha(float alpha);
        void SetAlpha(const std::string &alpha);
        float GetAlpha() const;

        void SetTextColor(int color);
        void SetTextColor(unsigned int color);
        void SetTextColor(const ImVec4 &color);
        void SetTextColor(const std::string &color);
        ImVec4 GetTextColor() const;
        [[nodiscard]] bool HasTextColor() const;
    };
}

#endif //TREMA_ELEMENTSTYLE_H
