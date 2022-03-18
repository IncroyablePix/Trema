//
// Created by JajaFil on 3/18/2022.
//

#include "FileNotFoundException.h"

namespace Trema::View
{
    FileNotFoundException::FileNotFoundException(const char *const message) noexcept
            : runtime_error(message)
    {

    }
}