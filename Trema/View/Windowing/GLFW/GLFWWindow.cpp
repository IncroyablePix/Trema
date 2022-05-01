//
// Created by JajaFil on 5/1/2022.
//

#include <sstream>
#include "GLFWWindow.h"
#include "GLFWBackendStrategy.h"
#include "../WindowInitializationException.h"

namespace Trema::View
{
    GLFWWindow::GLFWWindow(const WindowInfo &info) :
        Window(info),
        m_window(CreateWindow(info))
    {
        InitializeDearImGUI();
        InitializeVulkan(std::make_shared<GLFWBackendStrategy>(m_window));
        m_renderer->Init();
        m_renderer->LoadFonts();
    }

    GLFWWindow::~GLFWWindow()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void GLFWWindow::PollEvent()
    {
        if(glfwWindowShouldClose(m_window))
        {
            m_opened = false;
            return;
        }

        glfwPollEvents();
        m_renderer->ResizeSwapChain();
    }

    void GLFWWindow::SetTitle(const std::string &title)
    {
        glfwSetWindowTitle(m_window, title.c_str());
    }

    std::shared_ptr<GLFWWindow> GLFWWindow::CreateGLFWWindow(const WindowInfo &info)
    {
        return std::make_shared<GLFWWindow>(info);
    }

    void GLFWWindow::InitializeGlfw()
    {
        if(!GlfwInitialized)
        {
            if (!glfwInit())
            {
                std::stringstream ss;
                ss << "Error during GLFW initialization.";
                throw WindowInitializationException(ss.str().c_str());
            }

            if (!glfwVulkanSupported())
            {
                std::stringstream ss;
                ss << "Vulkan not supported by GLFW.";
                throw WindowInitializationException(ss.str().c_str());
            }

            GlfwInitialized = true;
        }
    }

    GLFWwindow *GLFWWindow::CreateWindow(const WindowInfo &info)
    {
        InitializeGlfw();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        return glfwCreateWindow(info.Width, info.Height, "Trema window", nullptr, nullptr);
    }
} // View