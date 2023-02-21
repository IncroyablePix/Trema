#ifndef TREMA_FAMILYEXCEPTION_H
#define TREMA_FAMILYEXCEPTION_H

#include <stdexcept>

namespace Trema::View
{
    class FamilyException : public std::runtime_error
    {
    public:
        explicit FamilyException(char const* message) noexcept;
    };
}

#endif //TREMA_FAMILYEXCEPTION_H
