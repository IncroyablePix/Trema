//
// Created by JajaFil on 2/12/2022.
//

#ifndef TREMA_IWINDOW_H
#define TREMA_IWINDOW_H

#include <string>
#include "Components/Layout/ILayout.h"
#include "Components/TopMenu/TopMenu.h"
#include "Components/IPopupComponent.h"
#include "ImGUI/imgui.h"
#include <unordered_map>
#include <vector>

namespace Trema::View
{
    struct WindowInfo
    {
        double SecondsPerUpdate;
        int Width;
        int Height;
    };

    class IWindow : public std::enable_shared_from_this<IWindow>
    {
    public:
        explicit IWindow(const WindowInfo &info);
        virtual void Resize(int width, int height) = 0;
        virtual void PollEvent() = 0;
        virtual bool IsOpened() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual int Run() = 0;
        virtual void Close() = 0;
        virtual void SetTitle(const std::string &title) = 0;
        void SetDefaultFont(const std::string &name);
        void AddFont(const std::string& path, float size = 12.0f, const std::string& name = "");
        void Build();
        void ApplyStyle();

        void SetLayout(std::shared_ptr<ILayout> layout);
        void SetTopMenu(std::shared_ptr<TopMenu> topMenu);

        inline void AddElementId(const std::string& id, std::shared_ptr<IGuiElement> element)
        {
            m_elementsById[id] = std::move(element);
        }

        template<class T> std::shared_ptr<T> GetElementById(const std::string& id)
        {
            if(m_elementsById.find(id) == m_elementsById.end())
                return nullptr;

            auto element = m_elementsById[id];

            if(!dynamic_cast<T*>(element.get()))
                return nullptr;

            return std::dynamic_pointer_cast<T>(element);
        }

        template<class T> void AddPopupComponent(std::shared_ptr<T> component)
        {
            m_popupComponents[typeid(T).name()] = std::move(component);
        }

        template<class T> std::shared_ptr<T> GetComponent()
        {
            auto typeName = typeid(T).name();
            if(m_popupComponents.find(typeName) == m_popupComponents.end())
                return nullptr;

            auto element = m_popupComponents[typeName];

            if(!dynamic_cast<T*>(element.get()))
                return nullptr;

            return std::dynamic_pointer_cast<T>(element);
        }

        ElementStyle Style;

    protected:
        std::unordered_map<std::string, std::shared_ptr<IGuiElement>> m_elementsById;
        std::shared_ptr<ILayout> m_layout;
        std::shared_ptr<TopMenu> m_menu;
        std::string m_title;
        std::unordered_map<std::string, ImFont*> m_fonts;
        ImFont* m_standardFont;
        double m_secondsPerUpdate { };
        int m_width;
        int m_height;

        std::unordered_map<std::string, std::shared_ptr<IPopupComponent>> m_popupComponents;
    };
}

#endif //TREMA_IWINDOW_H
