//
// Created by JajaFil on 2/12/2022.
//

#ifndef TREMA_IWINDOW_H
#define TREMA_IWINDOW_H

#include <string>
#include "../Components/Layout/Layout.h"
#include "../Components/TopMenu/TopMenu.h"
#include "../Components/IPopupComponent.h"
#include "../ImGUI/imgui.h"
#include "Vulkan/IWindowBackendStrategy.h"
#include "WindowInfo.h"
#include "Vulkan/VulkanRenderer.h"
#include "IRenderImage.h"
#include <unordered_map>
#include <vector>

namespace Trema::View
{
    class Window : public std::enable_shared_from_this<Window>
    {
    public:
        Window(const WindowInfo &info);
        Window operator=(const Window&) = delete;
        Window(const VulkanRenderer&) = delete;

        virtual void PollEvent() = 0;
        virtual void SetTitle(const std::string &title) = 0;
        virtual void ToggleFullscreen(bool fullscreen) = 0;
        virtual void ToggleTitleBar(bool titleBar) = 0;
        virtual void ToggleWindowOptions(bool fullscreen, bool titleBar) = 0;
        virtual void SetSize(int width, int height) = 0;
        virtual void SetWidth(int width) = 0;
        virtual void SetHeight(int height) = 0;

        int Run();
        void InitializeDearImGUI() const;
        void SetDefaultFont(const std::string &name);
        void AddFont(const std::string& path, float size = 12.0f, const std::string& name = "");
        std::shared_ptr<IRenderImage> AddImage(const std::string& image, const std::string& source);
        void Build();
        void Update();
        void UploadFonts();
        void ApplyStyle();
        void Resize(int width, int height);
        void Render();
        void Close();
        bool IsOpened() const;
        void InitializeVulkan(std::shared_ptr<IWindowBackendStrategy> windowBackendStrategy);

        void SetLayout(std::shared_ptr<Layout> layout);
        void SetTopMenu(std::shared_ptr<TopMenu> topMenu);

        inline bool IsFullscreen() const { return m_fullscreen; }
        inline bool IsTitleBarEnabled() const { return m_titleBar; }

        inline void AddElementId(const std::string& id, std::shared_ptr<GuiElement> element)
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
        std::unordered_map<std::string, std::shared_ptr<GuiElement>> m_elementsById;
        std::shared_ptr<Layout> m_layout;
        std::shared_ptr<TopMenu> m_menu;
        std::shared_ptr<IWindowBackendStrategy> m_windowBackendStrategy;

        std::string m_title { "Trema" };
        int m_width;
        int m_height;

        ImFont* m_standardFont;
        std::shared_ptr<VulkanRenderer> m_renderer;
        bool m_opened;
        bool m_fullscreen { false };
        bool m_titleBar { false };

        std::unordered_map<std::string, std::shared_ptr<IPopupComponent>> m_popupComponents;
        std::unordered_map<std::string, std::shared_ptr<IRenderImage>> m_renderImages;
    };
}

#endif //TREMA_IWINDOW_H
