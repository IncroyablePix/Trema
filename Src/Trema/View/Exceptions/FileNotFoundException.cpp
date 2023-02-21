#include "FileNotFoundException.h"

namespace Trema::View
{
    FileNotFoundException::FileNotFoundException(const char *const message) noexcept
            : runtime_error(message)
    {

    }
}