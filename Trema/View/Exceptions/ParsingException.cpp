//
// Created by JajaFil on 2/19/2022.
//

#include "ParsingException.h"

namespace Trema::View
{
    ParsingException::ParsingException(const char *const message) noexcept
            : runtime_error(message)
    {

    }
}