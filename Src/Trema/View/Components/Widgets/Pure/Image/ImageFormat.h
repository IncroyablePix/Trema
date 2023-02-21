#ifndef TREMA_PROJECT_IMAGEFORMAT_H
#define TREMA_PROJECT_IMAGEFORMAT_H

namespace Trema::View
{
    enum class ImageFormat
    {
        None,
        RGBA,
        RGBA32F
    };

    char BytesPerPixel(ImageFormat format);
}

#endif //TREMA_PROJECT_IMAGEFORMAT_H
