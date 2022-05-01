//
// Created by JajaFil on 5/1/2022.
//

#ifndef TREMA_PROJECT_GLFWBACKENDSTRATEGY_H
#define TREMA_PROJECT_GLFWBACKENDSTRATEGY_H

#include "../Vulkan/IWindowBackendStrategy.h"
#include <GLFW/glfw3.h>

namespace Trema::View
{
    class GLFWBackendStrategy : public IWindowBackendStrategy
    {
    public:
        explicit GLFWBackendStrategy(GLFWwindow* window);
        void InitWindowBackend() override;
        const char **GetExtensions(uint32_t &extensionCount) override;
        VkSurfaceKHR CreateSurface(VkInstance instance, VkAllocationCallbacks* allocator, VkResult &error) override;
        void GetWindowDimensions(int &width, int &height) override;

        void BeginNewFrame() const override;

    private:
        GLFWwindow* m_window;
    };

} // Trema

#endif //TREMA_PROJECT_GLFWBACKENDSTRATEGY_H
