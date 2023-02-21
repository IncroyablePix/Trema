#ifndef TREMA_PROJECT_VULKAN_H
#define TREMA_PROJECT_VULKAN_H

#include <vulkan/vulkan_core.h>
#include <cstdlib>

namespace Trema::View
{
    void CheckVkResult(VkResult error);
}

#endif //TREMA_PROJECT_VULKAN_H
