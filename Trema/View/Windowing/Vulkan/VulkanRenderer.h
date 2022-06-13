//
// Created by JajaFil on 2/12/2022.
//

#ifndef TREMA_VULKANRENDERER_H
#define TREMA_VULKANRENDERER_H

#include <vulkan/vulkan.h>
#include <memory>
#include "../../ImGUI/imgui_impl_vulkan.h"
#include "IWindowBackendStrategy.h"
#include "../../Components/Widgets/Pure/Image/ImageFormat.h"
#include <functional>
#include <vector>

#ifdef _DEBUG
#define IMGUI_VULKAN_DEBUG_REPORT
#endif

#ifdef IMGUI_VULKAN_DEBUG_REPORT
static VKAPI_ATTR VkBool32 VKAPI_CALL DebugReport(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData)
{
    (void)flags; (void)object; (void)location; (void)messageCode; (void)pUserData; (void)pLayerPrefix; // Unused arguments
    fprintf(stderr, "[vulkan] Debug report from ObjectType: %i\nMessage: %s\n\n", objectType, pMessage);
    return VK_FALSE;
}
#endif // IMGUI_VULKAN_DEBUG_REPORT

namespace Trema::View
{
    class VulkanRenderer : public std::enable_shared_from_this<VulkanRenderer>
    {
    public:
        explicit VulkanRenderer(std::shared_ptr<IWindowBackendStrategy> windowBackendStrategy);
        VulkanRenderer operator=(const VulkanRenderer&) = delete;
        VulkanRenderer(const VulkanRenderer&) = delete;
        ~VulkanRenderer();
        void Init();
        void LoadFonts();
        void Clear();
        void Render(ImGui_ImplVulkanH_Window* window, ImDrawData* drawData);
        void FramePresent(ImGui_ImplVulkanH_Window* window);
        void ResizeSwapChain();
        inline VkDevice GetDevice() const { return m_device; }
        inline VkPhysicalDevice GetPhysicalDevice() const { return m_physicalDevice; }
        inline ImGui_ImplVulkanH_Window* GetWindowData() { return &m_mainWindowData; }

        static VkFormat GetVulkanFormat(ImageFormat imageFormat);
        uint32_t GetVulkanMemoryType(VkMemoryPropertyFlags properties, uint32_t type_bits) const;
        void SubmitResourceFree(std::function<void()>&& func);
        void FlushCommandBuffer(VkCommandBuffer commandBuffer);
        VkCommandBuffer GetCommandBuffer(bool begin);

        void UploadFonts();

    private:
        VkAllocationCallbacks* m_allocator = VK_NULL_HANDLE;
        VkInstance m_instance = VK_NULL_HANDLE;
        VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
        VkDevice m_device = VK_NULL_HANDLE;
        uint32_t m_queueFamily = (uint32_t)-1;
        VkQueue m_queue = VK_NULL_HANDLE;
        VkDebugReportCallbackEXT m_debugReport = VK_NULL_HANDLE;
        VkPipelineCache m_pipelineCache = VK_NULL_HANDLE;
        VkDescriptorPool m_descriptorPool = VK_NULL_HANDLE;

        uint32_t m_currentFrameIndex = 0;

        std::vector<std::vector<VkCommandBuffer>> m_allocatedCommandBuffers;
        std::vector<std::vector<std::function<void()>>> m_resourceFreeQueue;

        ImGui_ImplVulkanH_Window m_mainWindowData;
        uint32_t m_minImageCount = 2;
        bool m_swapChainRebuild = false;

        ImVec4 m_clearColor = { 0.45f, 0.55f, 0.6f, 1.0f };
        std::shared_ptr<IWindowBackendStrategy> m_windowBackendStrategy;

        //---
        void SetupVulkan(const char** extensions, uint32_t extensionCount);
        void SetupVulkanWindow(ImGui_ImplVulkanH_Window* window, VkSurfaceKHR surface, int width, int height);
        void CleanupVulkan();
        void CleanupVulkanWindow();
        void InitializeVulkan(const char **extensions, uint32_t extensionCount);
        void SelectGPU();
        void SelectGraphicsQueueFamily();
        void CreateLogicalDevice();
        void CreateDescriptorPool();

        void FreeResourcesInQueue();
        void FreeCommandBuffers(ImGui_ImplVulkanH_Window *window, ImGui_ImplVulkanH_Frame* fd);
        static void SendRenderPass(ImGui_ImplVulkanH_Window *window, ImGui_ImplVulkanH_Frame* fd);
        static void RenderData(ImDrawData* drawData, ImGui_ImplVulkanH_Frame* fd);
        void SubmitCommandBuffer(VkSemaphore imageAcquiredSemaphore, VkSemaphore renderCompleteSemaphore, ImGui_ImplVulkanH_Frame* fd);
    };
}

#endif //TREMA_VULKANRENDERER_H
