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

        std::string m_width { "auto" };
        std::string m_height { "auto" };

        ImVec4 m_textColor = {1.0f, 1.0f, 1.0f, 1.0f };
        bool m_hasTextColor { false };

        ImVec4 m_backgroundColor = {1.0f, 1.0f, 1.0f, 1.0f };
        bool m_hasBackgroundColor { false };

        ImVec2 m_padding = { 0.0f, 0.0f };

        float m_rounding { 0.0f };

        std::string m_font;

        static bool GetFromPercents(const std::string& value, float& floatValue);
        static bool GetFromWord(const std::string& value, float& floatValue);

    public:
        void SetPaddingX(float x);
        void SetPaddingY(float y);
        void SetPadding(float x, float y);
        void SetPadding(ImVec2 padding);
        ImVec2 GetPadding() const;

        void SetRounding(float rounding);
        float GetRounding() const;

        void SetOrientation(enum Orientation orientation);
        void SetOrientation(const std::string &orientation);
        enum Orientation GetOrientation() const;

        void SetAlpha(float alpha);
        void SetAlpha(const std::string &alpha);
        float GetAlpha() const;

        void SetFont(std::string fontName);
        std::string& GetFont();

        void SetWidth(std::string width);
        void SetHeight(std::string height);

        ImVec2 GetSize() const;

        void SetTextColor(int color);
        void SetTextColor(unsigned int color);
        void SetTextColor(const ImVec4 &color);
        ImVec4 GetTextColor() const;
        [[nodiscard]] bool HasTextColor() const;

        void SetBackgroundColor(int color);
        void SetBackgroundColor(unsigned int color);
        void SetBackgroundColor(const ImVec4 &color);
        ImVec4 GetBackgroundColor() const;
        [[nodiscard]] bool HasBackgroundColor() const;
    };
}

#endif //TREMA_ELEMENTSTYLE_H
