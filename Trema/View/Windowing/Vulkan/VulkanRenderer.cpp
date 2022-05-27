//
// Created by JajaFil on 2/12/2022.
//
// Shamelessly sucked out of Dear ImGUI examples ; abstracted by myself
//

#include "VulkanRenderer.h"
#include "../WindowInitializationException.h"
#include "IWindowBackendStrategy.h"
#include "Vulkan.h"
#include "../../ImGUI/Extensions/ImPlot/implot.h"

#undef IMGUI_VULKAN_DEBUG_REPORT

namespace Trema::View
{
    VulkanRenderer::VulkanRenderer(std::shared_ptr<IWindowBackendStrategy> windowBackendStrategy) :
            m_windowBackendStrategy(std::move(windowBackendStrategy))
    {
        uint32_t extensionCount = 0;
        auto extensions = m_windowBackendStrategy->GetExtensions(extensionCount);
        SetupVulkan(extensions, extensionCount);

        //---
        VkResult err;
        VkSurfaceKHR surface = m_windowBackendStrategy->CreateSurface(m_instance, m_allocator, err);

        //---
        int w, h;
        m_windowBackendStrategy->GetWindowDimensions(w, h);
        SetupVulkanWindow(GetWindowData(), surface, w, h);

        m_allocatedCommandBuffers.resize(GetWindowData()->ImageCount);
        m_resourceFreeQueue.resize(GetWindowData()->ImageCount);
    }

    void VulkanRenderer::Init()
    {
        ImGui_ImplVulkanH_Window* wd = GetWindowData();
        m_windowBackendStrategy->InitWindowBackend();
        ImGui_ImplVulkan_InitInfo initInfo =
                {
                        .Instance = m_instance,
                        .PhysicalDevice = m_physicalDevice,
                        .Device = m_device,
                        .QueueFamily = m_queueFamily,
                        .Queue = m_queue,
                        .PipelineCache = m_pipelineCache,
                        .DescriptorPool = m_descriptorPool,
                        .MinImageCount = m_minImageCount,
                        .ImageCount = wd->ImageCount,
                        .Allocator = m_allocator,
                        .CheckVkResultFn = CheckVkResult
                };

        ImGui_ImplVulkan_Init(&initInfo, wd->RenderPass);
    }

    VulkanRenderer::~VulkanRenderer()
    {
        VkResult error;
        error = vkDeviceWaitIdle(m_device);
        CheckVkResult(error);

        for(auto &queue : m_resourceFreeQueue)
        {
            for(auto &f : queue)
            {
                f();
            }
        }
        m_resourceFreeQueue.clear();

        ImGui_ImplVulkan_Shutdown();
        ImPlot::DestroyContext();
        ImGui::DestroyContext();
        CleanupVulkanWindow();
        CleanupVulkan();
    }

    void VulkanRenderer::LoadFonts()
    {
        ImGui_ImplVulkanH_Window* wd = &m_mainWindowData;
        VkResult error;

        {
            VkCommandPool commandPool = wd->Frames[wd->FrameIndex].CommandPool;
            VkCommandBuffer commandBuffer = wd->Frames[wd->FrameIndex].CommandBuffer;

            error = vkResetCommandPool(m_device, commandPool, 0);
            CheckVkResult(error);
            VkCommandBufferBeginInfo beginInfo = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
            beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
            error = vkBeginCommandBuffer(commandBuffer, &beginInfo);
            CheckVkResult(error);

            ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);

            VkSubmitInfo endInfo =
                    {
                            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                            .commandBufferCount = 1,
                            .pCommandBuffers = &commandBuffer
                    };
            error = vkEndCommandBuffer(commandBuffer);
            CheckVkResult(error);
            error = vkQueueSubmit(m_queue, 1, &endInfo, VK_NULL_HANDLE);
            CheckVkResult(error);

            error = vkDeviceWaitIdle(m_device);
            CheckVkResult(error);
            ImGui_ImplVulkan_DestroyFontUploadObjects();
        }
    }

    void VulkanRenderer::SetupVulkanWindow(ImGui_ImplVulkanH_Window *window, VkSurfaceKHR surface, int width, int height)
    {
        window->Surface = surface;

        VkBool32 res;
        vkGetPhysicalDeviceSurfaceSupportKHR(m_physicalDevice, m_queueFamily, window->Surface, &res);
        if (res != VK_TRUE)
        {
            throw WindowInitializationException("Vulkan Error: No WSI support on physical device 0");
        }

        const VkFormat requestSurfaceImageFormat[] = { VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM };
        const VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
        window->SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(m_physicalDevice, window->Surface, requestSurfaceImageFormat, (size_t)IM_ARRAYSIZE(requestSurfaceImageFormat), requestSurfaceColorSpace);

#ifdef IMGUI_UNLIMITED_FRAME_RATE
        VkPresentModeKHR presentModes[] = { VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_FIFO_KHR };
#else
        VkPresentModeKHR presentModes[] = { VK_PRESENT_MODE_FIFO_KHR };
#endif
        window->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(m_physicalDevice, window->Surface, &presentModes[0], IM_ARRAYSIZE(presentModes));

        IM_ASSERT(m_minImageCount >= 2);
        ImGui_ImplVulkanH_CreateOrResizeWindow(m_instance, m_physicalDevice, m_device, window, m_queueFamily, m_allocator, width, height, m_minImageCount);
    }

    void VulkanRenderer::InitializeVulkan(const char **extensions, uint32_t extensionCount)
    {
        VkResult error;
        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.enabledExtensionCount = extensionCount;
        createInfo.ppEnabledExtensionNames = extensions;
#ifdef IMGUI_VULKAN_DEBUG_REPORT
        // Enabling validation layers
        const char* layers[] = { "VK_LAYER_KHRONOS_validation" };
        createInfo.enabledLayerCount = 1;
        createInfo.ppEnabledLayerNames = layers;

        // Enable debug report extension (we need additional storage, so we duplicate the user array to add our new extension to it)
        const char** extensions_ext = (const char**)malloc(sizeof(const char*) * (extensionCount + 1));
        memcpy(extensions_ext, extensions, extensionCount * sizeof(const char*));
        extensions_ext[extensionCount] = "VK_EXT_debug_report";
        createInfo.enabledExtensionCount = extensionCount + 1;
        createInfo.ppEnabledExtensionNames = extensions_ext;

        // Create Vulkan Instance
        err = vkCreateInstance(&createInfo, m_allocator, &m_instance);
        CheckVkResult(err);
        free(extensions_ext);

        // Get the function pointer (required for any extensions)
        auto vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(m_instance, "vkCreateDebugReportCallbackEXT");
        IM_ASSERT(vkCreateDebugReportCallbackEXT != NULL);

        // Setup the debug report callback
        VkDebugReportCallbackCreateInfoEXT debug_report_ci = {};
        debug_report_ci.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        debug_report_ci.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
        debug_report_ci.pfnCallback = debug_report;
        debug_report_ci.pUserData = NULL;
        err = vkCreateDebugReportCallbackEXT(m_instance, &debug_report_ci, g_Allocator, &g_DebugReport);
        CheckVkResult(err);
#else
        // Create Vulkan Instance without any debug feature
        error = vkCreateInstance(&createInfo, m_allocator, &m_instance);
        CheckVkResult(error);
        IM_UNUSED(m_debugReport);
#endif
    }

    void VulkanRenderer::SelectGPU()
    {
        VkResult error;
        uint32_t gpuCount;
        error = vkEnumeratePhysicalDevices(m_instance, &gpuCount, nullptr);
        CheckVkResult(error);
        IM_ASSERT(gpuCount > 0);

        auto* gpus = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * gpuCount);
        error = vkEnumeratePhysicalDevices(m_instance, &gpuCount, gpus);
        CheckVkResult(error);

        int useGPU = 0;
        for (int i = 0; i < (int)gpuCount; i++)
        {
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(gpus[i], &properties);
            if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            {
                useGPU = i;
                break;
            }
        }

        m_physicalDevice = gpus[useGPU];
        free(gpus);
    }

    void VulkanRenderer::SelectGraphicsQueueFamily()
    {
        uint32_t count;
        vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &count, nullptr);
        auto queues = new VkQueueFamilyProperties[count];
        vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &count, queues);
        for (uint32_t i = 0; i < count; i++)
        {
            if (queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                m_queueFamily = i;
                break;
            }
        }
        delete []queues;
        IM_ASSERT(m_queueFamily != (uint32_t)-1);
    }

    void VulkanRenderer::CreateLogicalDevice()
    {
        VkResult error;
        int deviceExtensionCount = 1;
        const char* deviceExtensions[] = {"VK_KHR_swapchain" };
        const float queuePriority[] = {1.0f };
        VkDeviceQueueCreateInfo queueInfo[1] = {};
        queueInfo[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfo[0].queueFamilyIndex = m_queueFamily;
        queueInfo[0].queueCount = 1;
        queueInfo[0].pQueuePriorities = queuePriority;
        VkDeviceCreateInfo createInfo =
                {
                        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                        .queueCreateInfoCount = sizeof(queueInfo) / sizeof(queueInfo[0]),
                        .pQueueCreateInfos = queueInfo,
                        .enabledExtensionCount = static_cast<uint32_t>(deviceExtensionCount),
                        .ppEnabledExtensionNames = deviceExtensions,
                };
        error = vkCreateDevice(m_physicalDevice, &createInfo, m_allocator, &m_device);
        CheckVkResult(error);
        vkGetDeviceQueue(m_device, m_queueFamily, 0, &m_queue);
    }

    void VulkanRenderer::CreateDescriptorPool()
    {
        VkResult error;
        VkDescriptorPoolSize pool_sizes[] =
                {
                        { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
                        { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
                        { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
                        { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
                        { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
                        { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
                        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
                        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
                        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
                        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
                        { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
                };
        VkDescriptorPoolCreateInfo poolInfo =
                {
                        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
                        .flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
                        .maxSets = 1000 * IM_ARRAYSIZE(pool_sizes),
                        .poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes),
                        .pPoolSizes = pool_sizes,
                };

        error = vkCreateDescriptorPool(m_device, &poolInfo, m_allocator, &m_descriptorPool);
        CheckVkResult(error);
    }

    void VulkanRenderer::SetupVulkan(const char **extensions, uint32_t extensionCount)
    {
        InitializeVulkan(extensions, extensionCount);
        SelectGPU();
        SelectGraphicsQueueFamily();
        CreateLogicalDevice();
        CreateDescriptorPool();
    }

    void VulkanRenderer::CleanupVulkan()
    {
        vkDestroyDescriptorPool(m_device, m_descriptorPool, m_allocator);

#ifdef IMGUI_VULKAN_DEBUG_REPORT
        // Remove the debug report callback
    auto vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(m_instance, "vkDestroyDebugReportCallbackEXT");
    vkDestroyDebugReportCallbackEXT(m_instance, m_debugReport, m_allocator);
#endif // IMGUI_VULKAN_DEBUG_REPORT

        vkDestroyDevice(m_device, m_allocator);
        vkDestroyInstance(m_instance, m_allocator);
    }

    void VulkanRenderer::CleanupVulkanWindow()
    {
        ImGui_ImplVulkanH_DestroyWindow(m_instance, m_device, &m_mainWindowData, m_allocator);
    }

    void VulkanRenderer::FreeResourcesInQueue()
    {
        for(auto& freeFunction : m_resourceFreeQueue[m_currentFrameIndex])
            freeFunction();

        m_resourceFreeQueue[m_currentFrameIndex].clear();
    }

    void VulkanRenderer::FreeCommandBuffers(ImGui_ImplVulkanH_Window *window, ImGui_ImplVulkanH_Frame* fd)
    {
        VkResult err;
        auto& allocatedCommandBuffers = m_allocatedCommandBuffers[window->FrameIndex];
        if (!allocatedCommandBuffers.empty())
        {
            vkFreeCommandBuffers(m_device, fd->CommandPool, (uint32_t)allocatedCommandBuffers.size(), allocatedCommandBuffers.data());
            allocatedCommandBuffers.clear();
        }

        err = vkResetCommandPool(m_device, fd->CommandPool, 0);
        CheckVkResult(err);
        VkCommandBufferBeginInfo info = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
        info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
        CheckVkResult(err);
    }

    void VulkanRenderer::SendRenderPass(ImGui_ImplVulkanH_Window *window, ImGui_ImplVulkanH_Frame* fd)
    {
        VkRenderPassBeginInfo info =
                {
                        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                        .renderPass = window->RenderPass,
                        .framebuffer = fd->Framebuffer,
                        .renderArea =
                                {
                                        .extent =
                                                {
                                                        .width = static_cast<uint32_t>(window->Width),
                                                        .height = static_cast<uint32_t>(window->Height),
                                                }
                                },
                        .clearValueCount = 1,
                        .pClearValues = &window->ClearValue,
                };

        vkCmdBeginRenderPass(fd->CommandBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
    }

    void VulkanRenderer::SubmitCommandBuffer(VkSemaphore imageAcquiredSemaphore, VkSemaphore renderCompleteSemaphore, ImGui_ImplVulkanH_Frame* fd)
    {
        VkResult err;
        vkCmdEndRenderPass(fd->CommandBuffer);
        {
            VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            VkSubmitInfo info =
                    {
                            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                            .waitSemaphoreCount = 1,
                            .pWaitSemaphores = &imageAcquiredSemaphore,
                            .pWaitDstStageMask = &wait_stage,
                            .commandBufferCount = 1,
                            .pCommandBuffers = &fd->CommandBuffer,
                            .signalSemaphoreCount = 1,
                            .pSignalSemaphores = &renderCompleteSemaphore,
                    };

            err = vkEndCommandBuffer(fd->CommandBuffer);
            CheckVkResult(err);
            err = vkQueueSubmit(m_queue, 1, &info, fd->Fence);
            CheckVkResult(err);
        }
    }

    void VulkanRenderer::RenderData(ImDrawData* drawData, ImGui_ImplVulkanH_Frame* fd)
    {
        ImGui_ImplVulkan_RenderDrawData(drawData, fd->CommandBuffer);
    }

    void VulkanRenderer::Render(ImGui_ImplVulkanH_Window *window, ImDrawData *drawData)
    {
        VkResult err;

        VkSemaphore imageAcquiredSemaphore  = window->FrameSemaphores[window->SemaphoreIndex].ImageAcquiredSemaphore;
        VkSemaphore renderCompleteSemaphore = window->FrameSemaphores[window->SemaphoreIndex].RenderCompleteSemaphore;
        err = vkAcquireNextImageKHR(m_device, window->Swapchain, UINT64_MAX, imageAcquiredSemaphore, VK_NULL_HANDLE, &window->FrameIndex);
        if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
        {
            m_swapChainRebuild = true;
            return;
        }
        CheckVkResult(err);

        m_currentFrameIndex = (m_currentFrameIndex + 1) % m_mainWindowData.ImageCount;

        ImGui_ImplVulkanH_Frame* fd = &window->Frames[window->FrameIndex];
        {
            err = vkWaitForFences(m_device, 1, &fd->Fence, VK_TRUE, UINT64_MAX);    // wait indefinitely instead of periodically checking
            CheckVkResult(err);

            err = vkResetFences(m_device, 1, &fd->Fence);
            CheckVkResult(err);
        }

        FreeResourcesInQueue();
        FreeCommandBuffers(window, fd);
        SendRenderPass(window, fd);

        RenderData(drawData, fd);
        SubmitCommandBuffer(imageAcquiredSemaphore, renderCompleteSemaphore, fd);
    }

    void VulkanRenderer::FramePresent(ImGui_ImplVulkanH_Window *window)
    {
        if (m_swapChainRebuild)
            return;

        VkSemaphore renderCompleteSemaphore = window->FrameSemaphores[window->SemaphoreIndex].RenderCompleteSemaphore;
        VkPresentInfoKHR info =
                {
                        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                        .waitSemaphoreCount = 1,
                        .pWaitSemaphores = &renderCompleteSemaphore,
                        .swapchainCount = 1,
                        .pSwapchains = &window->Swapchain,
                        .pImageIndices = &window->FrameIndex,
                };

        VkResult err = vkQueuePresentKHR(m_queue, &info);
        if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
        {
            m_swapChainRebuild = true;
            return;
        }
        CheckVkResult(err);
        window->SemaphoreIndex = (window->SemaphoreIndex + 1) % window->ImageCount; // Now we can use the next set of semaphores
    }

    void VulkanRenderer::ResizeSwapChain()
    {
        int w, h;
        m_windowBackendStrategy->GetWindowDimensions(w, h);

        if(w > 0 && h > 0)
        {
            ImGui_ImplVulkan_SetMinImageCount(m_minImageCount);
            ImGui_ImplVulkanH_CreateOrResizeWindow(m_instance, m_physicalDevice, m_device, &m_mainWindowData, m_queueFamily, m_allocator, w, h, m_minImageCount);
            m_mainWindowData.FrameIndex = 0;

            m_allocatedCommandBuffers.clear();
            m_allocatedCommandBuffers.resize(m_mainWindowData.ImageCount);

            m_swapChainRebuild = false;
        }
    }

    void VulkanRenderer::Clear()
    {
        auto* wd = GetWindowData();
        wd->ClearValue.color.float32[0] = m_clearColor.x * m_clearColor.w;
        wd->ClearValue.color.float32[1] = m_clearColor.y * m_clearColor.w;
        wd->ClearValue.color.float32[2] = m_clearColor.z * m_clearColor.w;
        wd->ClearValue.color.float32[3] = m_clearColor.w;
    }

    void VulkanRenderer::UploadFonts()
    {
        VkResult err;
        auto* wd = GetWindowData();
        auto commandPool = wd->Frames[wd->FrameIndex].CommandPool;
        auto commandBuffer = wd->Frames[wd->FrameIndex].CommandBuffer;

        err = vkResetCommandPool(m_device, commandPool, 0);
        CheckVkResult(err);

        VkCommandBufferBeginInfo beginInfo = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
        beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        err = vkBeginCommandBuffer(commandBuffer, &beginInfo);
        CheckVkResult(err);

        ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);

        VkSubmitInfo endInfo =
        {
            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .commandBufferCount = 1,
            .pCommandBuffers = &commandBuffer
        };

        err = vkEndCommandBuffer(commandBuffer);
        CheckVkResult(err);
        err = vkQueueSubmit(m_queue, 1, &endInfo, VK_NULL_HANDLE);
        CheckVkResult(err);

        err = vkDeviceWaitIdle(m_device);
        CheckVkResult(err);
        ImGui_ImplVulkan_DestroyFontUploadObjects();
    }

    VkFormat VulkanRenderer::GetVulkanFormat(ImageFormat imageFormat)
    {
        switch (imageFormat)
        {
            case ImageFormat::RGBA:
                return VK_FORMAT_R8G8B8A8_UNORM;
            case ImageFormat::RGBA32F:
                return VK_FORMAT_R32G32B32A32_SFLOAT;
            case ImageFormat::None:
                break;
        }
        return (VkFormat)0;
    }

    uint32_t VulkanRenderer::GetVulkanMemoryType(VkMemoryPropertyFlags properties, uint32_t type_bits) const
    {
        VkPhysicalDeviceMemoryProperties prop;
        vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &prop);
        for (uint32_t i = 0; i < prop.memoryTypeCount; i++)
        {
            if ((prop.memoryTypes[i].propertyFlags & properties) == properties && type_bits & (1 << i))
            {
                return i;
            }
        }

        return 0xffffffff;
    }

    void VulkanRenderer::SubmitResourceFree(std::function<void()> &&func)
    {
        m_resourceFreeQueue[m_currentFrameIndex].emplace_back(func);
    }

    void VulkanRenderer::FlushCommandBuffer(VkCommandBuffer commandBuffer)
    {
        const uint64_t DEFAULT_FENCE_TIMEOUT = 100000000000;

        VkSubmitInfo end_info =
                {
                    .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                    .commandBufferCount = 1,
                    .pCommandBuffers = &commandBuffer,
                };
        auto err = vkEndCommandBuffer(commandBuffer);
        CheckVkResult(err);

        VkFenceCreateInfo fenceCreateInfo =
                {

                        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
                        .flags = 0,
                };
        VkFence fence;
        err = vkCreateFence(m_device, &fenceCreateInfo, nullptr, &fence);
        CheckVkResult(err);

        err = vkQueueSubmit(m_queue, 1, &end_info, fence);
        CheckVkResult(err);

        err = vkWaitForFences(m_device, 1, &fence, VK_TRUE, DEFAULT_FENCE_TIMEOUT);
        CheckVkResult(err);

        vkDestroyFence(m_device, fence, nullptr);
    }

    VkCommandBuffer VulkanRenderer::GetCommandBuffer(bool begin)
    {
        ImGui_ImplVulkanH_Window* wd = &m_mainWindowData;

        // Use any command queue
        VkCommandPool command_pool = wd->Frames[wd->FrameIndex].CommandPool;

        VkCommandBufferAllocateInfo cmdBufAllocateInfo =
                {
                        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                        .commandPool = command_pool,
                        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
                        .commandBufferCount = 1,
                };


        VkCommandBuffer& commandBuffer = m_allocatedCommandBuffers[wd->FrameIndex].emplace_back();
        auto err = vkAllocateCommandBuffers(m_device, &cmdBufAllocateInfo, &commandBuffer);
        CheckVkResult(err);

        VkCommandBufferBeginInfo beginInfo = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
        beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        err = vkBeginCommandBuffer(commandBuffer, &beginInfo);
        CheckVkResult(err);

        return commandBuffer;
    }
}