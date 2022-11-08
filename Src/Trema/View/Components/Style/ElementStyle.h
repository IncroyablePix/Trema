//
// Created by JajaFil on 3/6/2022.
//

#ifndef TREMA_ELEMENTSTYLE_H
#define TREMA_ELEMENTSTYLE_H

#include <string>
#include <imgui.h>
#include "StyleColor.h"
#include <functional>

namespace Trema::View
{
    enum Orientation
    {
        Column,
        Row
    };

    enum Alignment
    {
        Start,
        Center,
        End
    };

    class ElementStyle
    {
    private:
        float m_alpha = 1.f;                // Transparency
        Orientation m_orientation = Column; // Orientation (radio buttons, ...)
        Alignment m_verticalAlignment = Start;
        Alignment m_horizontalAlignment = Start;

        std::string m_width { "auto" };
        std::string m_height { "auto" };

        std::string m_marginTop { "0" };
        std::string m_marginBottom { "0" };
        std::string m_marginLeft { "0" };
        std::string m_marginRight { "0" };

        StyleColor m_textColor;
        StyleColor m_textColorDisabled;
        StyleColor m_windowBackgroundColor;
        StyleColor m_widgetBackgroundColor;
        StyleColor m_widgetBackgroundColorHover;
        StyleColor m_widgetBackgroundColorActive;
        StyleColor m_buttonBackgroundColor;
        StyleColor m_buttonBackgroundColorHover;
        StyleColor m_buttonBackgroundColorActive;
        StyleColor m_menuBackgroundColor;
        StyleColor m_headerColor;
        StyleColor m_headerColorActive;
        StyleColor m_tableHeaderActive;
        StyleColor m_popupBackgroundColor;
        StyleColor m_sliderGrabColor;
        StyleColor m_sliderGrabActiveColor;

        ImVec2 m_windowPadding = {8.0f, 8.0f };
        ImVec2 m_framePadding = { 4.0f, 3.0f };

        float m_frameRounding { 0.0f };
        float m_windowRounding { 0.0f };

        bool m_windowHeader { true };

        std::string m_font;

        static bool GetFromPercents(const std::string& value, float& floatValue);
        static bool GetFromWord(const std::string& value, float& floatValue);
        static bool GetFromPx(const std::string &value, float &floatValue);

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
        void SetOrientation(const std::string_view &orientation);
        enum Orientation GetOrientation() const;

        void SetHorizontalAlignment(enum Alignment alignment);
        void SetHorizontalAlignment(const std::string_view &alignment);
        enum Alignment GetHorizontalAlignment() const;

        void SetVerticalAlignment(enum Alignment alignment);
        void SetVerticalAlignment(const std::string_view &alignment);
        enum Alignment GetVerticalAlignment() const;

        void SetAlpha(float alpha);
        void SetAlpha(const std::string &alpha);
        float GetAlpha() const;

        void SetFont(std::string fontName);
        std::string& GetFont();

        void SetWidth(std::string width);
        void SetHeight(std::string height);

        void SetMarginTop(std::string top);
        void SetMarginBottom(std::string bottom);
        void SetMarginLeft(std::string left);
        void SetMarginRight(std::string right);

        ImVec2 GetSize() const;
        ImVec4 GetMargin() const;

        inline StyleColor& TextColor() { return m_textColor; }
        inline StyleColor& TextDisabledColor() { return m_textColorDisabled; }
        inline StyleColor& WindowColor() { return m_windowBackgroundColor; }
        inline StyleColor& WidgetBackgroundColor() { return m_widgetBackgroundColor; }
        inline StyleColor& WidgetBackgroundColorHover() { return m_widgetBackgroundColorHover; }
        inline StyleColor& WidgetBackgroundColorActive() { return m_widgetBackgroundColorActive; }
        inline StyleColor& ButtonColor() { return m_buttonBackgroundColor; }
        inline StyleColor& ButtonColorHover() { return m_buttonBackgroundColorHover; }
        inline StyleColor& ButtonColorActive() { return m_buttonBackgroundColorActive; }
        inline StyleColor& MenuBackgroundColor() { return m_menuBackgroundColor; }
        inline StyleColor& HeaderColor() { return m_headerColor; }
        inline StyleColor& HeaderActiveColor() { return m_headerColorActive; }
        inline StyleColor& TableHeaderColor() { return m_tableHeaderActive; }
        inline StyleColor& PopupBackgroundColor() { return m_popupBackgroundColor; }
        inline StyleColor& SliderGrabColor() { return m_sliderGrabColor; }
        inline StyleColor& SliderGrabActiveColor() { return m_sliderGrabActiveColor; }
    };
}

#endif //TREMA_ELEMENTSTYLE_H
