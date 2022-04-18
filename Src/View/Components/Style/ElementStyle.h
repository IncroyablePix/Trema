//
// Created by JajaFil on 3/6/2022.
//

#ifndef TREMA_ELEMENTSTYLE_H
#define TREMA_ELEMENTSTYLE_H

#include <string>
#include "../../ImGUI/imgui.h"
#include "StyleColor.h"
#include <functional>

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
        Orientation m_orientation = Column; // Orientation (radio buttons, ...)

        std::string m_width { "auto" };
        std::string m_height { "auto" };

        StyleColor m_textColor;
        StyleColor m_textColorDisabled;
        StyleColor m_windowBackgroundColor;
        StyleColor m_widgetBackgroundColor;
        StyleColor m_menuBackgroundColor;
        StyleColor m_headerColor;
        StyleColor m_headerColorActive;
        StyleColor m_tableHeaderActive;
        StyleColor m_popupBackgroundColor;

        ImVec2 m_windowPadding = {0.0f, 0.0f };
        ImVec2 m_framePadding = { 0.0f, 0.0f };

        float m_frameRounding { 0.0f };
        float m_windowRounding { 0.0f };

        bool m_windowHeader { true };

        std::string m_font;

        static bool GetFromPercents(const std::string& value, float& floatValue);
        static bool GetFromWord(const std::string& value, float& floatValue);

    public:
        void SetWindowPaddingX(float x);
        void SetWindowPaddingY(float y);
        void SetWindowPadding(float x, float y);
        void SetWindowPadding(ImVec2 padding);
        ImVec2 GetWindowPadding() const;

        void SetFramePaddingX(float x);
        void SetFramePaddingY(float y);
        void SetFramePadding(float x, float y);
        void SetFramePadding(ImVec2 padding);
        ImVec2 GetFramePadding() const;

        void SetWindowRounding(float rounding);
        float GetWindowRounding() const;

        void SetFrameRounding(float rounding);
        float GetFrameRounding() const;

        void SetWindowHeaderVisibility(bool toggle);
        bool GetWindowHeaderVisibility() const;

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

        inline StyleColor& TextColor() { return m_textColor; }
        inline StyleColor& TextDisabledColor() { return m_textColorDisabled; }
        inline StyleColor& WindowColor() { return m_windowBackgroundColor; }
        inline StyleColor& WidgetBackgroundColor() { return m_widgetBackgroundColor; }
        inline StyleColor& MenuBackgroundColor() { return m_menuBackgroundColor; }
        inline StyleColor& HeaderColor() { return m_headerColor; }
        inline StyleColor& HeaderActiveColor() { return m_headerColorActive; }
        inline StyleColor& TableHeaderColor() { return m_tableHeaderActive; }
        inline StyleColor& PopupBackgroundColor() { return m_popupBackgroundColor; }
    };
}

#endif //TREMA_ELEMENTSTYLE_H
