//
// Created by JajaFil on 5/1/2022.
//

#include "GLFWBackendStrategy.h"
#include "../../ImGUI/imgui_impl_glfw.h"

namespace Trema
{
    View::GLFWBackendStrategy::GLFWBackendStrategy(GLFWwindow *window) : m_window(window)
    {

    }

    void View::GLFWBackendStrategy::InitWindowBackend()
    {
        ImGui_ImplGlfw_InitForVulkan(m_window, true);
    }

    const char **View::GLFWBackendStrategy::GetExtensions(uint32_t &extensionCount)
    {
        return glfwGetRequiredInstanceExtensions(&extensionCount);
    }

    VkSurfaceKHR View::GLFWBackendStrategy::CreateSurface(VkInstance instance, VkAllocationCallbacks* allocator, VkResult &error)
    {
        VkSurfaceKHR surface;
        error = glfwCreateWindowSurface(instance, m_window, allocator, &surface);
        return surface;
    }

    void View::GLFWBackendStrategy::GetWindowDimensions(int &width, int &height)
    {
        glfwGetFramebufferSize(m_window, &width, &height);
    }

    void View::GLFWBackendStrategy::BeginNewFrame() const
    {
        ImGui_ImplGlfw_NewFrame();
    }
} // Trema