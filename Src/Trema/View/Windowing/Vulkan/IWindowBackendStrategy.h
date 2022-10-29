//
// Created by JajaFil on 5/1/2022.
//

#ifndef TREMA_PROJECT_IWINDOWBACKENDSTRATEGY_H
#define TREMA_PROJECT_IWINDOWBACKENDSTRATEGY_H

#include <cstdint>
#include <vulkan/vulkan_core.h>
#include <memory>

namespace Trema::View
{
    class IWindowBackendStrategy : public std::enable_shared_from_this<IWindowBackendStrategy>
    {
    public:
        virtual ~IWindowBackendStrategy() = default;
        virtual void InitWindowBackend() = 0;
        virtual void BeginNewFrame() const = 0;
        virtual const char ** GetExtensions(uint32_t& extensionCount) = 0;
        virtual VkSurfaceKHR CreateSurface(VkInstance instance, VkAllocationCallbacks* allocator, VkResult &error) = 0;
        virtual void GetWindowDimensions(int& width, int& height) = 0;
    };
}

#endif //TREMA_PROJECT_IWINDOWBACKENDSTRATEGY_H
