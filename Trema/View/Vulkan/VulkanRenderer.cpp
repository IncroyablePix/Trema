//
// Created by JajaFil on 2/12/2022.
//

#include <SDL2/SDL_vulkan.h>
#include "VulkanRenderer.h"
#include "../WindowInitializationException.h"
#include "../ImGUI/imgui_impl_sdl.h"

#undef IMGUI_VULKAN_DEBUG_REPORT

namespace Trema::View
{
    VulkanRenderer::VulkanRenderer(const WindowInfo &info, SDL_Window* window)
    {
        uint32_t extensionCount = 0;
        SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);
        const char **extensions = new const char*[extensionCount];
        SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensions);
        SetupVulkan(extensions, extensionCount);
        delete[] extensions;

        //---

        VkSurfaceKHR surface;

        if(SDL_Vulkan_CreateSurface(window, m_instance, &surface) == 0)
        {
            throw WindowInitializationException("Failed to create Vulkan surface.");
        }

        //---
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        SetupVulkanWindow(GetWindowData(), surface, w, h);

        //---
    }

    void VulkanRenderer::Init(SDL_Window* window)
    {
        ImGui_ImplVulkanH_Window* wd = GetWindowData();
        ImGui_ImplSDL2_InitForVulkan(window);
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

        ImGui_ImplVulkan_Shutdown();
        ImGui::DestroyContext();
        CleanupVulkanWindow();
        CleanupVulkan();
    }

    void VulkanRenderer::LoadFonts()
    {
        ImGui_ImplVulkanH_Window* wd = &m_mainWindowData;
        VkResult error;
        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != NULL);

        // Upload Fonts
        {
            // Use any command queue
            VkCommandPool commandPool = wd->Frames[wd->FrameIndex].CommandPool;
            VkCommandBuffer commandBuffer = wd->Frames[wd->FrameIndex].CommandBuffer;

            error = vkResetCommandPool(m_device, commandPool, 0);
            CheckVkResult(error);
            VkCommandBufferBeginInfo begin_info = {};
            begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
            error = vkBeginCommandBuffer(commandBuffer, &begin_info);
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

        // Check for WSI support
        VkBool32 res;
        vkGetPhysicalDeviceSurfaceSupportKHR(m_physicalDevice, m_queueFamily, window->Surface, &res);
        if (res != VK_TRUE)
        {
            throw WindowInitializationException("Vulkan Error: No WSI support on physical device 0");
        }

        // Select Surface Format
        const VkFormat requestSurfaceImageFormat[] = { VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM };
        const VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
        window->SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(m_physicalDevice, window->Surface, requestSurfaceImageFormat, (size_t)IM_ARRAYSIZE(requestSurfaceImageFormat), requestSurfaceColorSpace);

        // Select Present Mode
#ifdef IMGUI_UNLIMITED_FRAME_RATE
        VkPresentModeKHR presentModes[] = { VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_FIFO_KHR };
#else
        VkPresentModeKHR presentModes[] = { VK_PRESENT_MODE_FIFO_KHR };
#endif
        window->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(m_physicalDevice, window->Surface, &presentModes[0], IM_ARRAYSIZE(presentModes));
        //printf("[vulkan] Selected PresentMode = %d\n", window->PresentMode);

        // Create SwapChain, RenderPass, Framebuffer, etc.
        IM_ASSERT(m_minImageCount >= 2);
        ImGui_ImplVulkanH_CreateOrResizeWindow(m_instance, m_physicalDevice, m_device, window, m_queueFamily, m_allocator, width, height, m_minImageCount);
    }

    void VulkanRenderer::SetupVulkan(const char **extensions, uint32_t extensionCount)
    {
        VkResult error;
        // Create Vulkan Instance
        {
            VkInstanceCreateInfo create_info = {};
            create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            create_info.enabledExtensionCount = extensionCount;
            create_info.ppEnabledExtensionNames = extensions;
#ifdef IMGUI_VULKAN_DEBUG_REPORT
            // Enabling validation layers
        const char* layers[] = { "VK_LAYER_KHRONOS_validation" };
        create_info.enabledLayerCount = 1;
        create_info.ppEnabledLayerNames = layers;

        // Enable debug report extension (we need additional storage, so we duplicate the user array to add our new extension to it)
        const char** extensions_ext = (const char**)malloc(sizeof(const char*) * (extensionCount + 1));
        memcpy(extensions_ext, extensions, extensionCount * sizeof(const char*));
        extensions_ext[extensionCount] = "VK_EXT_debug_report";
        create_info.enabledExtensionCount = extensionCount + 1;
        create_info.ppEnabledExtensionNames = extensions_ext;

        // Create Vulkan Instance
        err = vkCreateInstance(&create_info, m_allocator, &m_instance);
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
            error = vkCreateInstance(&create_info, m_allocator, &m_instance);
            CheckVkResult(error);
            IM_UNUSED(m_debugReport);
#endif
        }

        // Select GPU
        {
            uint32_t gpu_count;
            error = vkEnumeratePhysicalDevices(m_instance, &gpu_count, nullptr);
            CheckVkResult(error);
            IM_ASSERT(gpu_count > 0);

            auto* gpus = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * gpu_count);
            error = vkEnumeratePhysicalDevices(m_instance, &gpu_count, gpus);
            CheckVkResult(error);

            // If a number >1 of GPUs got reported, find discrete GPU if present, or use first one available. This covers
            // most common cases (multi-gpu/integrated+dedicated graphics). Handling more complicated setups (multiple
            // dedicated GPUs) is out of scope of this sample.
            int use_gpu = 0;
            for (int i = 0; i < (int)gpu_count; i++)
            {
                VkPhysicalDeviceProperties properties;
                vkGetPhysicalDeviceProperties(gpus[i], &properties);
                if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                {
                    use_gpu = i;
                    break;
                }
            }

            m_physicalDevice = gpus[use_gpu];
            free(gpus);
        }

        // Select graphics queue family
        {
            uint32_t count;
            vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &count, NULL);
            VkQueueFamilyProperties* queues = (VkQueueFamilyProperties*)malloc(sizeof(VkQueueFamilyProperties) * count);
            vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &count, queues);
            for (uint32_t i = 0; i < count; i++)
            {
                if (queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
                {
                    m_queueFamily = i;
                    break;
                }
            }
            free(queues);
            IM_ASSERT(m_queueFamily != (uint32_t)-1);
        }

        // Create Logical Device (with 1 queue)
        {
            int device_extension_count = 1;
            const char* device_extensions[] = { "VK_KHR_swapchain" };
            const float queue_priority[] = { 1.0f };
            VkDeviceQueueCreateInfo queue_info[1] = {};
            queue_info[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queue_info[0].queueFamilyIndex = m_queueFamily;
            queue_info[0].queueCount = 1;
            queue_info[0].pQueuePriorities = queue_priority;
            VkDeviceCreateInfo create_info = {};
            create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            create_info.queueCreateInfoCount = sizeof(queue_info) / sizeof(queue_info[0]);
            create_info.pQueueCreateInfos = queue_info;
            create_info.enabledExtensionCount = device_extension_count;
            create_info.ppEnabledExtensionNames = device_extensions;
            error = vkCreateDevice(m_physicalDevice, &create_info, m_allocator, &m_device);
            CheckVkResult(error);
            vkGetDeviceQueue(m_device, m_queueFamily, 0, &m_queue);
        }

        // Create Descriptor Pool
        {
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
            VkDescriptorPoolCreateInfo pool_info = {};
            pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
            pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
            pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
            pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
            pool_info.pPoolSizes = pool_sizes;
            error = vkCreateDescriptorPool(m_device, &pool_info, m_allocator, &m_descriptorPool);
            CheckVkResult(error);
        }
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

    void VulkanRenderer::CheckVkResult(VkResult error)
    {
        if (error == 0)
            return;
        //fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
        if (error < 0)
            abort();
    }

    void VulkanRenderer::Render(ImGui_ImplVulkanH_Window *window, ImDrawData *drawData)
    {
        VkResult err;

        VkSemaphore image_acquired_semaphore  = window->FrameSemaphores[window->SemaphoreIndex].ImageAcquiredSemaphore;
        VkSemaphore render_complete_semaphore = window->FrameSemaphores[window->SemaphoreIndex].RenderCompleteSemaphore;
        err = vkAcquireNextImageKHR(m_device, window->Swapchain, UINT64_MAX, image_acquired_semaphore, VK_NULL_HANDLE, &window->FrameIndex);
        if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
        {
            m_swapChainRebuild = true;
            return;
        }
        CheckVkResult(err);

        ImGui_ImplVulkanH_Frame* fd = &window->Frames[window->FrameIndex];
        {
            err = vkWaitForFences(m_device, 1, &fd->Fence, VK_TRUE, UINT64_MAX);    // wait indefinitely instead of periodically checking
            CheckVkResult(err);

            err = vkResetFences(m_device, 1, &fd->Fence);
            CheckVkResult(err);
        }
        {
            err = vkResetCommandPool(m_device, fd->CommandPool, 0);
            CheckVkResult(err);
            VkCommandBufferBeginInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
            err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
            CheckVkResult(err);
        }
        {
            VkRenderPassBeginInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            info.renderPass = window->RenderPass;
            info.framebuffer = fd->Framebuffer;
            info.renderArea.extent.width = window->Width;
            info.renderArea.extent.height = window->Height;
            info.clearValueCount = 1;
            info.pClearValues = &window->ClearValue;
            vkCmdBeginRenderPass(fd->CommandBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
        }

        // Record dear imgui primitives into command buffer
        ImGui_ImplVulkan_RenderDrawData(drawData, fd->CommandBuffer);

        // Submit command buffer
        vkCmdEndRenderPass(fd->CommandBuffer);
        {
            VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            VkSubmitInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            info.waitSemaphoreCount = 1;
            info.pWaitSemaphores = &image_acquired_semaphore;
            info.pWaitDstStageMask = &wait_stage;
            info.commandBufferCount = 1;
            info.pCommandBuffers = &fd->CommandBuffer;
            info.signalSemaphoreCount = 1;
            info.pSignalSemaphores = &render_complete_semaphore;

            err = vkEndCommandBuffer(fd->CommandBuffer);
            CheckVkResult(err);
            err = vkQueueSubmit(m_queue, 1, &info, fd->Fence);
            CheckVkResult(err);
        }
    }

    void VulkanRenderer::FramePresent(ImGui_ImplVulkanH_Window *window)
    {
        if (m_swapChainRebuild)
            return;

        VkSemaphore render_complete_semaphore = window->FrameSemaphores[window->SemaphoreIndex].RenderCompleteSemaphore;
        VkPresentInfoKHR info = {};
        info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        info.waitSemaphoreCount = 1;
        info.pWaitSemaphores = &render_complete_semaphore;
        info.swapchainCount = 1;
        info.pSwapchains = &window->Swapchain;
        info.pImageIndices = &window->FrameIndex;
        VkResult err = vkQueuePresentKHR(m_queue, &info);
        if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
        {
            m_swapChainRebuild = true;
            return;
        }
        CheckVkResult(err);
        window->SemaphoreIndex = (window->SemaphoreIndex + 1) % window->ImageCount; // Now we can use the next set of semaphores
    }

    void VulkanRenderer::ResizeSwapChain(SDL_Window* window)
    {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);

        if(w > 0 && h > 0)
        {
            ImGui_ImplVulkan_SetMinImageCount(m_minImageCount);
            ImGui_ImplVulkanH_CreateOrResizeWindow(m_instance, m_physicalDevice, m_device, &m_mainWindowData, m_queueFamily, m_allocator, w, h, m_minImageCount);
            m_mainWindowData.FrameIndex = 0;
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

        VkCommandBufferBeginInfo beginInfo = { };
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
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
}