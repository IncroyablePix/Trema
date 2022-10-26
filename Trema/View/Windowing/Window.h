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
#include "../Style/Parser/IStyleParser.h"
#include "../Activities/ActivityBuilder.h"
#include "../Activities/IStateManager.h"
#include <unordered_map>
#include <vector>

namespace Trema::View
{
    class Activity;
    class ViewParser;
    class Window : public std::enable_shared_from_this<Window>
    {
    public:
        Window(const WindowInfo &info, std::unique_ptr<ViewParser> viewParser);
        Window(const VulkanRenderer&) = delete;

        virtual void PollEvent() = 0;
        virtual void SetTitle(const std::string &title) = 0;
        virtual void ToggleFullscreen(bool fullscreen) = 0;
        virtual void ToggleTitleBar(bool titleBar) = 0;
        virtual void ToggleWindowOptions(bool fullscreen, bool titleBar) = 0;
        virtual void SetSize(int width, int height) = 0;
        virtual void SetWidth(int width) = 0;
        virtual void SetHeight(int height) = 0;
        virtual void SwapBuffers() = 0;
        virtual void UpdateTime() = 0;
        virtual void SetWindowIcon(const std::string &path) = 0;

        int Run();
        void InitializeDearImGUI() const;
        void SetDefaultFont(const std::string &name);
        void AddFont(const std::string& path, float size = 12.0f, const std::string& name = "");
        std::shared_ptr<IRenderImage> AddImage(const std::string& image, const std::string& source);
        void Build();
        void Update();
        void UploadFonts();
        void Resize(int width, int height);
        void Render();
        void Close();
        bool IsOpened() const;
        void InitializeVulkan(std::shared_ptr<IWindowBackendStrategy> windowBackendStrategy);
        void LoadView(const std::string &path);
        void StartActivityForResult(std::unique_ptr<Activity> activity);
        void QuitActivity(uint16_t requestCode, uint16_t resultCode, Intent intent);

        inline bool IsFullscreen() const { return m_fullscreen; }

        inline bool IsTitleBarEnabled() const { return m_titleBar; }

        template<class T> void AddPopupComponent(std::shared_ptr<T> component)
        {
            m_popupComponents[typeid(T).name()] = std::move(component);
        }

        template<class T> std::shared_ptr<T> GetComponent()
        {
            auto typeName = typeid(T).name();
            if(!m_popupComponents.contains(typeName))
                return nullptr;

            auto element = m_popupComponents[typeName];

            if(!dynamic_cast<T*>(element.get()))
                return nullptr;

            return std::dynamic_pointer_cast<T>(element);
        }

    protected:
        std::shared_ptr<IWindowBackendStrategy> m_windowBackendStrategy;
        std::unique_ptr<ViewParser> m_viewParser;

        std::string m_title { "Trema" };
        int m_width;
        int m_height;

        ImFont* m_standardFont;
        std::string m_standardFontName { "" };
        std::shared_ptr<VulkanRenderer> m_renderer;
        bool m_opened;
        bool m_fullscreen { false };
        bool m_titleBar { false };
        double m_deltaTime { 0.0 };

        std::unique_ptr<IStateManager> m_stateManager;

        std::unordered_map<std::string, std::shared_ptr<IPopupComponent>> m_popupComponents;
        std::unordered_map<std::string, std::shared_ptr<IRenderImage>> m_renderImages;
        std::deque<std::function<void(void)>> m_postRenderRoutines;

    private:
        void BuildFontAtlas();
        void ConsumePostRenderRoutines();
    };
}

#endif //TREMA_IWINDOW_H
