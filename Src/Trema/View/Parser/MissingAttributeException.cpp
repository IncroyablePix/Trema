//
// Created by Benjam on 11/7/2022.
//

#include "MissingAttributeException.h"

namespace Trema::View
{
    MissingAttributeException::MissingAttributeException(const char *message) noexcept
            : runtime_error(message)
    {

    }
}