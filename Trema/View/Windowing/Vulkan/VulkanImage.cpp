//
// Created by JajaFil on 5/11/2022.
//
// Shamelessly stolen and customized from Walnut (https://github.com/TheCherno/Walnut/)
//

#include <array>
#include "VulkanImage.h"
#include "VulkanRenderer.h"
#include "../../ImGUI/imgui_impl_vulkan.h"
#include "../../STB/stb_image.h"
#include "Vulkan.h"

namespace Trema::View
{
    VulkanImage::VulkanImage(std::string path, std::shared_ptr<VulkanRenderer> renderer) :
        m_renderer(std::move(renderer)),
        m_filePath(std::move(path))
    {
        int width;
        int height;
        int channels;

        uint8_t const* data;

        if(stbi_is_hdr(m_filePath.c_str()))
        {
            data = (uint8_t*)stbi_loadf(m_filePath.c_str(), &width, &height, &channels, 4);
            m_format = ImageFormat::RGBA32F;
        }
        else
        {
            data = stbi_load(m_filePath.c_str(), &width, &height, &channels, 4);
            m_format = ImageFormat::RGBA;
        }

        m_width = width;
        m_height = height;

        AllocateMemory();
        SetData(data);
    }

    VulkanImage::VulkanImage(uint32_t width, uint32_t height, ImageFormat format, std::shared_ptr<VulkanRenderer> renderer, const void* data) :
        m_renderer(std::move(renderer)),
        m_width(width),
        m_height(height),
        m_format(format)
    {
        AllocateMemory();

        if (data)
        {
            SetData(data);
        }
    }

    VulkanImage::~VulkanImage()
    {
        m_renderer->SubmitResourceFree([sampler = m_sampler, imageView = m_imageView, image = m_image,
                                               memory = m_memory, stagingBuffer = m_stagingBuffer, stagingBufferMemory = m_stagingBufferMemory,
                                               this]()
                                       {
                                           VkDevice device = m_renderer->GetDevice();

                                           vkDestroySampler(device, sampler, nullptr);
                                           vkDestroyImageView(device, imageView, nullptr);
                                           vkDestroyImage(device, image, nullptr);
                                           vkFreeMemory(device, memory, nullptr);
                                           vkDestroyBuffer(device, stagingBuffer, nullptr);
                                           vkFreeMemory(device, stagingBufferMemory, nullptr);
                                       });
    }

    void VulkanImage::CreateUploadBuffer(size_t uploadSize)
    {
        VkResult err;
        VkDevice device = m_renderer->GetDevice();

        VkBufferCreateInfo bufferInfo =
                {
                        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                        .size = uploadSize,
                        .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
                };

        err = vkCreateBuffer(device, &bufferInfo, nullptr, &m_stagingBuffer);
        CheckVkResult(err);
        VkMemoryRequirements req;
        vkGetBufferMemoryRequirements(device, m_stagingBuffer, &req);
        m_alignedSize = req.size;
        VkMemoryAllocateInfo allocInfo =
                {
                        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                        .allocationSize = req.size,
                        .memoryTypeIndex = m_renderer->GetVulkanMemoryType(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, req.memoryTypeBits),
                };

        err = vkAllocateMemory(device, &allocInfo, nullptr, &m_stagingBufferMemory);
        CheckVkResult(err);
        err = vkBindBufferMemory(device, m_stagingBuffer, m_stagingBufferMemory, 0);
        CheckVkResult(err);
    }

    void VulkanImage::UploadToBuffer(const void* data, size_t uploadSize)
    {
        VkResult err;
        VkDevice device = m_renderer->GetDevice();
        char* map = nullptr;
        err = vkMapMemory(device, m_stagingBufferMemory, 0, m_alignedSize, 0, (void**)(&map));
        CheckVkResult(err);
        memcpy(map, data, uploadSize);
        std::array<VkMappedMemoryRange, 1> range = {};
        range[0].sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        range[0].memory = m_stagingBufferMemory;
        range[0].size = m_alignedSize;
        err = vkFlushMappedMemoryRanges(device, 1, range.data());
        CheckVkResult(err);
        vkUnmapMemory(device, m_stagingBufferMemory);
    }

    void VulkanImage::CopyDataToImage()
    {
        VkCommandBuffer commandBuffer = m_renderer->GetCommandBuffer(true);

        VkImageMemoryBarrier copyBarrier =
                {
                        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
                        .dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
                        .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                        .newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                        .image = m_image,
                        .subresourceRange =
                                {
                                        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                        .levelCount = 1,
                                        .layerCount = 1,
                                },
                };

        vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &copyBarrier);

        VkBufferImageCopy region =
                {
                        .imageSubresource =
                                {
                                        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                        .layerCount = 1,
                                },
                        .imageExtent =
                                {
                                        .width = m_width,
                                        .height = m_height,
                                        .depth = 1,
                                }
                };

        vkCmdCopyBufferToImage(commandBuffer, m_stagingBuffer, m_image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

        VkImageMemoryBarrier useBarrier =
                {
                        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
                        .srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
                        .dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
                        .oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                        .newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
                        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                        .image = m_image,
                        .subresourceRange =
                                {
                                        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                        .levelCount = 1,
                                        .layerCount = 1,
                                },
                };


        vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0,
                             nullptr, 0, nullptr, 1, &useBarrier);

        m_renderer->FlushCommandBuffer(commandBuffer);
    }

    void VulkanImage::SetData(const void* data)
    {
        size_t uploadSize = m_width * m_height * BytesPerPixel(m_format);

        if (!m_stagingBuffer)
        {
            CreateUploadBuffer(uploadSize);
        }

        UploadToBuffer(data, uploadSize);
        CopyDataToImage();
    }

    void VulkanImage::Reupload()
    {
        size_t uploadSize = m_width * m_height * BytesPerPixel(m_format);

        if (!m_stagingBuffer)
        {
            CreateUploadBuffer(uploadSize);
        }

        CopyDataToImage();
    }

    void VulkanImage::CreateImage(VkFormat vulkanFormat)
    {
        VkResult err;
        VkDevice device = m_renderer->GetDevice();
        VkImageCreateInfo info =
                {
                        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
                        .imageType = VK_IMAGE_TYPE_2D,
                        .format = vulkanFormat,
                        .extent =
                                {
                                        .width = m_width,
                                        .height = m_height,
                                        .depth = 1,
                                },
                        .mipLevels = 1,
                        .arrayLayers = 1,
                        .samples = VK_SAMPLE_COUNT_1_BIT,
                        .tiling = VK_IMAGE_TILING_OPTIMAL,
                        .usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
                        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
                        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                };

        err = vkCreateImage(device, &info, nullptr, &m_image);
        CheckVkResult(err);
        VkMemoryRequirements req;
        vkGetImageMemoryRequirements(device, m_image, &req);
        VkMemoryAllocateInfo allocInfo =
                {
                        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                        .allocationSize = req.size,
                        .memoryTypeIndex = m_renderer->GetVulkanMemoryType(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                                                                           req.memoryTypeBits),
                };

        err = vkAllocateMemory(device, &allocInfo, nullptr, &m_memory);
        CheckVkResult(err);
        err = vkBindImageMemory(device, m_image, m_memory, 0);
        CheckVkResult(err);
    }

    void VulkanImage::CreateImageView(VkFormat vulkanFormat)
    {
        VkResult err;
        VkDevice device = m_renderer->GetDevice();
        VkImageViewCreateInfo info =
                {
                        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
                        .image = m_image,
                        .viewType = VK_IMAGE_VIEW_TYPE_2D,
                        .format = vulkanFormat,
                        .subresourceRange =
                                {
                                        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                        .levelCount = 1,
                                        .layerCount = 1,
                                },
                };

        err = vkCreateImageView(device, &info, nullptr, &m_imageView);
        CheckVkResult(err);
    }

    void VulkanImage::CreateSampler()
    {
        VkResult err;
        VkDevice device = m_renderer->GetDevice();
        VkSamplerCreateInfo info =
                {
                        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                        .magFilter = VK_FILTER_LINEAR,
                        .minFilter = VK_FILTER_LINEAR,
                        .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
                        .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
                        .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
                        .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
                        .maxAnisotropy = 1.0f,
                        .minLod = -1000,
                        .maxLod = 1000,
                };

        err = vkCreateSampler(device, &info, nullptr, &m_sampler);
        CheckVkResult(err);
    }

    void VulkanImage::CreateDescriptorSet()
    {
        m_descriptorSet = ImGui_ImplVulkan_AddTexture(m_sampler, m_imageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    }

    void VulkanImage::AllocateMemory()
    {
        VkFormat vulkanFormat = m_renderer->GetVulkanFormat(m_format);

        CreateImage(vulkanFormat);
        CreateImageView(vulkanFormat);
        CreateSampler();
        CreateDescriptorSet();
    }
}