#ifndef TREMA_WINDOWINITIALIZATIONEXCEPTION_H
#define TREMA_WINDOWINITIALIZATIONEXCEPTION_H

#include <stdexcept>

namespace Trema::View
{
    class WindowInitializationException : public std::runtime_error
    {
    public:
        explicit WindowInitializationException(char const* const message) noexcept;
        //virtual char const* what() const noexcept;
    };
}

#endif //TREMA_WINDOWINITIALIZATIONEXCEPTION_H
