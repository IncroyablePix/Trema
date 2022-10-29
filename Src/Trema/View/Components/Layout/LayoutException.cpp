//
// Created by JajaFil on 3/29/2022.
//

#include "LayoutException.h"

namespace Trema::View
{
    LayoutException::LayoutException(const char *const message) noexcept
            : runtime_error(message)
    {

    }
}