#include <sstream>
#include "GLFWWindow.h"
#include "GLFWBackendStrategy.h"
#include "../WindowInitializationException.h"
#include "../Fonts/FontsRepository.h"
#include "../../Style/Parser/StackedStyleParser.h"
#include "../../Parser/TinyXML/TinyXMLViewParser.h"
#include <stb_image.h>
#include <filesystem>

namespace Trema::View
{
    GLFWWindow::GLFWWindow(const WindowInfo &info, std::unique_ptr<ViewParser> viewParser) :
        Window(info, std::move(viewParser)),
        m_window(nullptr)
    {
        CreateGlfwWindow();
    }

    GLFWWindow::~GLFWWindow()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void GLFWWindow::InitializeGlfwVulkan()
    {
        InitializeDearImGUI();
        InitializeVulkan(std::make_shared<GLFWBackendStrategy>(m_window));
        m_renderer->Init();
        FontsRepository::GetInstance()->ReloadFonts();
        for(const auto& [name, img] : m_renderImages)
        {
            img->Reupload();
        }

        UploadFonts();
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

    void GLFWWindow::CreateGlfwWindow()
    {
        InitializeGlfw();
        m_previousTime = glfwGetTime();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        if(m_window)
        {
            m_renderer.reset();
            glfwDestroyWindow(m_window);
        }

        if(m_fullscreen)
        {
            auto monitor = glfwGetPrimaryMonitor();
            const auto mode = glfwGetVideoMode(monitor);
            m_window = glfwCreateWindow(mode->width, mode->height, m_title.c_str(), monitor, nullptr);
        }
        else
        {
            m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
        }
        
        glfwSwapInterval(true);
        InitializeGlfwVulkan();
    }

    void GLFWWindow::ToggleWindowOptions(bool fullscreen, bool titleBar)
    {
        if (fullscreen != m_fullscreen || titleBar != m_titleBar)
        {
            ToggleFullscreen(fullscreen);
            m_titleBar = titleBar;
        }
    }

    void GLFWWindow::ToggleFullscreen(bool fullscreen)
    {
        if (fullscreen != m_fullscreen)
        {
            m_fullscreen = fullscreen;
            auto monitor = glfwGetPrimaryMonitor();
            const auto mode = glfwGetVideoMode(monitor);
            if(fullscreen)
                glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            else
                glfwSetWindowMonitor(m_window, nullptr, (mode->width / 2) - (m_width / 2), (mode->height / 2) - (m_height / 2), m_width, m_height, mode->refreshRate);
        }
    }

    void GLFWWindow::ToggleTitleBar(bool titleBar)
    {
        if (titleBar != m_titleBar)
        {
            m_titleBar = titleBar;
        }
    }

    void GLFWWindow::SetSize(int width, int height)
    {
        glfwSetWindowSize(m_window, m_width = width, m_height = height);
    }

    void GLFWWindow::SetWidth(int width)
    {
        if (width > 0)
        {
            glfwSetWindowSize(m_window, m_width = width, m_height);
        }
    }

    void GLFWWindow::SetHeight(int height)
    {
        if (height > 0)
        {
            glfwSetWindowSize(m_window, m_width, m_height = height);
        }
    }

    void GLFWWindow::SwapBuffers()
    {
        glfwSwapBuffers(m_window);
    }

    void GLFWWindow::UpdateTime()
    {
        double currentTime = glfwGetTime();
        m_deltaTime = currentTime - m_previousTime;
        m_previousTime = currentTime;
    }

    void GLFWWindow::SetWindowIcon(const std::string &path)
    {
        if(std::filesystem::exists(path))
        {
            GLFWimage images[1];
            images[0].pixels = stbi_load(path.c_str(), &images[0].width, &images[0].height, 0, 4);
            glfwSetWindowIcon(m_window, 1, images);
            stbi_image_free(images[0].pixels);
        }
    }
}
