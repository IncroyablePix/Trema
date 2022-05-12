//
// Created by JajaFil on 5/11/2022.
//

#include "ImageFormat.h"

namespace Trema::View
{
    char BytesPerPixel(ImageFormat format)
    {
        switch (format)
        {
            case ImageFormat::RGBA:
                return 4;
            case ImageFormat::RGBA32F:
                return 16;
            case ImageFormat::None:
                break;
        }
        return 0;
    }
}
