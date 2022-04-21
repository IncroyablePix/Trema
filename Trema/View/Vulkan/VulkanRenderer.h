//
// Created by JajaFil on 2/12/2022.
//

#ifndef TREMA_VULKANRENDERER_H
#define TREMA_VULKANRENDERER_H

#include <vulkan/vulkan.h>
#include <SDL2/SDL_video.h>
#include <memory>
#include "../ImGUI/imgui_impl_vulkan.h"
#include "../IWindow.h"

#ifdef _DEBUG
#define IMGUI_VULKAN_DEBUG_REPORT
#endif

#ifdef IMGUI_VULKAN_DEBUG_REPORT
static VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData)
{
    (void)flags; (void)object; (void)location; (void)messageCode; (void)pUserData; (void)pLayerPrefix; // Unused arguments
    fprintf(stderr, "[vulkan] Debug report from ObjectType: %i\nMessage: %s\n\n", objectType, pMessage);
    return VK_FALSE;
}
#endif // IMGUI_VULKAN_DEBUG_REPORT

namespace Trema::View
{
    class VulkanRenderer
    {
    public:
        VulkanRenderer(const WindowInfo &info, SDL_Window* window);
        ~VulkanRenderer();
        void Init(SDL_Window* window);
        void LoadFonts();
        void Clear();
        void Render(ImGui_ImplVulkanH_Window* window, ImDrawData* drawData);
        void FramePresent(ImGui_ImplVulkanH_Window* window);
        void ResizeSwapChain(SDL_Window* window);
        inline ImGui_ImplVulkanH_Window* GetWindowData() { return &m_mainWindowData; }

        static void CheckVkResult(VkResult error);

        void UploadFonts();

    private:
        VkAllocationCallbacks* m_allocator = nullptr;
        VkInstance m_instance = VK_NULL_HANDLE;
        VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
        VkDevice m_device = VK_NULL_HANDLE;
        uint32_t m_queueFamily = (uint32_t)-1;
        VkQueue m_queue = VK_NULL_HANDLE;
        VkDebugReportCallbackEXT m_debugReport = VK_NULL_HANDLE;
        VkPipelineCache m_pipelineCache = VK_NULL_HANDLE;
        VkDescriptorPool m_descriptorPool = VK_NULL_HANDLE;

        ImGui_ImplVulkanH_Window m_mainWindowData;
        uint32_t m_minImageCount = 2;
        bool m_swapChainRebuild = false;

        ImVec4 m_clearColor = { 0.45f, 0.55f, 0.6f, 1.0f };

        //---
        void SetupVulkan(const char** extensions, uint32_t extensionCount);
        void SetupVulkanWindow(ImGui_ImplVulkanH_Window* window, VkSurfaceKHR surface, int width, int height);
        void CleanupVulkan();
        void CleanupVulkanWindow();
    };
}

#endif //TREMA_VULKANRENDERER_H
