#include "Vulkan.h"

namespace Trema::View
{
    void CheckVkResult(VkResult error)
    {
        if (error == 0)
            return;
        //fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
        if (error < 0)
            abort();
    }
}
