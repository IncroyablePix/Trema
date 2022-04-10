//
// Created by JajaFil on 2/12/2022.
//

#include "WindowInitializationException.h"

namespace Trema::View
{
    WindowInitializationException::WindowInitializationException(const char *const message) noexcept
            : runtime_error(message)
    {

    }
}
/*char const *Trema::View::WindowInitializationException::what() const noexcept
{
    return runtime_error::what();
}
*/