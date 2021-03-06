//
// Created by JajaFil on 5/1/2022.
//

#ifndef TREMA_PROJECT_GLFWWINDOW_H
#define TREMA_PROJECT_GLFWWINDOW_H

#include "../Window.h"
#include <GLFW/glfw3.h>

namespace Trema::View
{
    class GLFWWindow : public Window
    {
    public:
        explicit GLFWWindow(const WindowInfo &info);
        GLFWWindow operator=(const GLFWWindow&) = delete;
        explicit GLFWWindow(const GLFWWindow&) = delete;
        ~GLFWWindow();
        void PollEvent() override;
        void SetTitle(const std::string &title) override;
        void ToggleFullscreen(bool fullscreen) override;
        void ToggleTitleBar(bool titleBar) override;
        void ToggleWindowOptions(bool fullscreen, bool titleBar) override;
        void SetSize(int width, int height) override;
        void SetWidth(int width) override;
        void SetHeight(int height) override;
        void SwapBuffers() override;

        static std::shared_ptr<GLFWWindow> CreateGLFWWindow(const WindowInfo &info = { .Width = 1280, .Height = 720 });

    private:
        GLFWwindow* m_window { nullptr };
        static void InitializeGlfw();
        void CreateWindow();
        void InitializeGlfwVulkan();
    };
    static bool GlfwInitialized { false };
}

#endif //TREMA_PROJECT_GLFWWINDOW_H
