#ifndef TREMA_DISPLAYEXCEPTION_H
#define TREMA_DISPLAYEXCEPTION_H


#include <stdexcept>

namespace Trema::View
{
    class DisplayException : public std::runtime_error
    {
    public:
        explicit DisplayException(char const* message) noexcept;
    };
};


#endif //TREMA_DISPLAYEXCEPTION_H
