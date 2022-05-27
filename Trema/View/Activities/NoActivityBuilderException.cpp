//
// Created by JajaFil on 5/22/2022.
//

#include "NoActivityBuilderException.h"

namespace Trema::View
{
    NoActivityBuilderException::NoActivityBuilderException(char const* message) : std::runtime_error(message)
    {

    }
}
