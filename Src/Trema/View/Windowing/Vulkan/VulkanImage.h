#ifndef TREMA_PROJECT_VULKANIMAGE_H
#define TREMA_PROJECT_VULKANIMAGE_H

#include <string>
#include <vulkan/vulkan_core.h>
#include "../../Components/Widgets/Pure/Image/ImageFormat.h"
#include "VulkanRenderer.h"
#include "../IRenderImage.h"

namespace Trema::View
{
    class VulkanImage : public IRenderImage
    {
    public:
        VulkanImage(std::string path, std::shared_ptr<VulkanRenderer> renderer);
        VulkanImage(uint32_t width, uint32_t height, ImageFormat format, std::shared_ptr<VulkanRenderer> renderer, const void* data = nullptr);
        VulkanImage operator=(const VulkanImage&) = delete;
        VulkanImage(const VulkanImage&) = delete;
        ~VulkanImage() override;

        void SetData(const void* data) final;
        void Reupload() final;

        inline VkDescriptorSet GetDescriptorSet() const { return m_descriptorSet; }
        inline float GetWidth() const override { return (float) m_width; }
        inline float GetHeight() const override { return (float) m_height; }
        inline ImTextureID GetTextureID() const override { return GetDescriptorSet(); }

    private:
        void AllocateMemory();
        void CreateUploadBuffer(size_t uploadSize);
        void UploadToBuffer(const void* data, size_t uploadSize);
        void CopyDataToImage();

        void CreateImage(VkFormat vulkanFormat);
        void CreateImageView(VkFormat vulkanFormat);
        void CreateSampler();
        void CreateDescriptorSet();

        std::shared_ptr<VulkanRenderer> m_renderer;

        uint32_t m_width = 0;
        uint32_t m_height = 0;

        VkImage m_image = nullptr;
        VkImageView m_imageView = nullptr;
        VkDeviceMemory m_memory = nullptr;
        VkSampler m_sampler = nullptr;

        ImageFormat m_format = ImageFormat::None;

        VkBuffer m_stagingBuffer = nullptr;
        VkDeviceMemory m_stagingBufferMemory = nullptr;

        size_t m_alignedSize = 0;
        VkDescriptorSet m_descriptorSet = nullptr;

        std::string m_filePath;
    };
};


#endif //TREMA_PROJECT_VULKANIMAGE_H
