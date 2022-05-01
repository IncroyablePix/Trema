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
        ~GLFWWindow();
        void PollEvent() override;
        void SetTitle(const std::string &title) override;

        static std::shared_ptr<GLFWWindow> CreateGLFWWindow(const WindowInfo &info);

    private:
        GLFWwindow* m_window;
        static void InitializeGlfw();
        static GLFWwindow* CreateWindow(const WindowInfo &info);
    };
    static bool GlfwInitialized { false };
}

#endif //TREMA_PROJECT_GLFWWINDOW_H
