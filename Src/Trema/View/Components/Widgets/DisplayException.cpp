#include "DisplayException.h"

namespace Trema::View
{
    DisplayException::DisplayException(const char *const message) noexcept:
        runtime_error(message)
    {

    }
};