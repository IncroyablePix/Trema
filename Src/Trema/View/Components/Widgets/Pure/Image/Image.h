// Inspired by Walnut project: https://github.com/TheCherno/Walnut
//

#ifndef TREMA_PROJECT_IMAGE_H
#define TREMA_PROJECT_IMAGE_H

#include <vulkan/vulkan.h>
#include "../../../GuiElement.h"
#include "ImageFormat.h"
#include "../../../../Windowing/IRenderImage.h"

namespace Trema::View
{
    class Image : public GuiElement
    {
    public:
        Image(std::shared_ptr<GuiElement> parent, std::string name, std::shared_ptr<IRenderImage> renderImage);
        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;
        void Show() override;

        static std::shared_ptr<Image> CreateImage(std::shared_ptr<GuiElement> parent, std::string name, std::shared_ptr<IRenderImage> renderImage);

    private:
        std::shared_ptr<IRenderImage> m_renderImage;
    };

} // Trema

#endif //TREMA_PROJECT_IMAGE_H
