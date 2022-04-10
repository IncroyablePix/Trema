//
// Created by JajaFil on 2/27/2022.
//

#include "FamilyException.h"

namespace Trema::View
{
    FamilyException::FamilyException(const char *message) noexcept: runtime_error(message)
    {

    }
}