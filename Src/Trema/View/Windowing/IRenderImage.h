#ifndef TREMA_PROJECT_IRENDERIMAGE_H
#define TREMA_PROJECT_IRENDERIMAGE_H


#include <imgui.h>

namespace Trema::View
{
    class IRenderImage
    {
    public:
        virtual ~IRenderImage() = default;
        virtual float GetWidth() const = 0;
        virtual float GetHeight() const = 0;
        virtual ImTextureID GetTextureID() const = 0;
        virtual void SetData(const void* data) = 0;
        virtual void Reupload() = 0;
    };
}

#endif //TREMA_PROJECT_IRENDERIMAGE_H
