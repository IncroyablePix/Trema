#include "WindowInitializationException.h"

namespace Trema::View
{
    WindowInitializationException::WindowInitializationException(const char *const message) noexcept
            : runtime_error(message)
    {

    }
}
