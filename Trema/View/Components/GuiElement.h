//
// Created by Benjam on 10/20/2021.
//

#ifndef MATH4BG_IGUIELEMENT_H
#define MATH4BG_IGUIELEMENT_H

#include <memory>
#include "Style/ElementStyle.h"

namespace Trema::View
{
    class GuiElement : public std::enable_shared_from_this<GuiElement>
    {
    public:
        GuiElement(std::shared_ptr<GuiElement> parent, std::string name);
        GuiElement(const GuiElement&) = delete;
        GuiElement& operator=(const GuiElement&) = delete;
        virtual ~GuiElement() = default;

        virtual void Show() = 0;
        virtual const std::string& GetName();
        inline const std::string& GetId() { return m_id; }
        inline void SetId(std::string id) { m_id = std::move(id); }
        virtual const char* NameId() const;
        virtual void SetName(std::string name);
        virtual void BeginStyle();
        virtual void EndStyle();
        virtual void PreShow();
        void PollEvents();

        virtual ImVec2 GetItemSize() const;
        inline ImVec2 GetLayoutSize() const { return m_layoutSize; }

        inline void SetDockSize(float dockSize) { m_dockSize = dockSize; }
        inline float GetDockSize() const { return m_dockSize; }

        void ShowContextMenu();

        ElementStyle Style;

    protected:
        template<class T>
        inline static bool IsType(const std::shared_ptr<GuiElement> &element) { return dynamic_cast<T*>(element.get()) != nullptr; }
        template<class T>
        inline static std::shared_ptr<T> CastTo(const std::shared_ptr<GuiElement> &element) { return std::dynamic_pointer_cast<T>(element); }
        inline void SetIsWindow(bool toggle) { m_isWindow = toggle; }
        inline ImVec2 GetParentSize() const { return m_parent ? m_parent->Style.GetSize() : ImVec2(0, 0); }
        inline bool IsTextHidden() const { return m_name.length() > 2 && m_name[0] == '#' && m_name[1] == '#'; }
        ImVec2 GetSize() const;
        virtual void AlignX();
        virtual void AlignY();

        bool m_isWindow { false };
        std::shared_ptr<GuiElement> m_parent;
        float m_dockSize { 0.2f };
        std::string m_name;
        std::string m_id;
        std::string m_contextMenu;
        unsigned int m_styles { 0 };
        unsigned int m_colors { 0 };

        std::string m_fontName;
        ImFont* m_font { nullptr };
        ImVec2 m_layoutSize { 0, 0 };

    private:
        static bool IsInWindow();
    };
}

#endif //MATH4BG_IGUIELEMENT_H
