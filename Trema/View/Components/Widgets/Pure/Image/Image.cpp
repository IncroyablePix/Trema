//
// Created by JajaFil on 5/4/2022.
//
// Inspired by Walnut project: https://github.com/TheCherno/Walnut
//

#include "Image.h"

#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include "../../../../STB/stb_image.h"
#include "../../../../Windowing/Vulkan/Vulkan.h"

namespace Trema::View
{

    Image::Image(std::shared_ptr<GuiElement> parent, std::string name, std::shared_ptr<IRenderImage> renderImage) :
            GuiElement(std::move(parent), std::move(name)),
            m_renderImage(std::move(renderImage))
    {

    }

    void Image::Show()
    {
        BeginStyle();

        auto size = Style.GetSize();
        auto x  = size.x;
        auto y = size.y;

        ImVec2 imageSize
                {
                    (x == 0 ? m_renderImage->GetWidth() : x),
                    (y == 0 ? m_renderImage->GetHeight() : y)
                };

        if(x == 0 && y != 0)
           imageSize.x = m_renderImage->GetWidth() * (y / m_renderImage->GetHeight());
        else if(x != 0 && y == 0)
            imageSize.y = m_renderImage->GetHeight() * (x / m_renderImage->GetWidth());

        ImGui::Image(m_renderImage->GetTextureID(), imageSize);

        EndStyle();
    }

    std::shared_ptr<Image> Image::CreateImage(std::shared_ptr<GuiElement> parent, std::string name, std::shared_ptr<IRenderImage> renderImage)
    {
        return std::make_shared<Image>(std::move(parent), std::move(name), std::move(renderImage));
    }
}