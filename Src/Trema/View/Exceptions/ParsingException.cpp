#include "ParsingException.h"

namespace Trema::View
{
    ParsingException::ParsingException(const char *const message) noexcept
            : runtime_error(message)
    {

    }
}