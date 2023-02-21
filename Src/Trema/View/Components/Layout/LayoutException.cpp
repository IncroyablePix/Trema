#include "LayoutException.h"

namespace Trema::View
{
    LayoutException::LayoutException(const char *const message) noexcept
            : runtime_error(message)
    {

    }
}