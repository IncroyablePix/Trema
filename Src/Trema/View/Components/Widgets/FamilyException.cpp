#include "FamilyException.h"

namespace Trema::View
{
    FamilyException::FamilyException(const char *message) noexcept: runtime_error(message)
    {

    }
}