//
// Created by JajaFil on 2/27/2022.
//

#ifndef TREMA_DISPLAYEXCEPTION_H
#define TREMA_DISPLAYEXCEPTION_H


#include <stdexcept>

namespace Trema::View
{
    class DisplayException : public std::runtime_error
    {
    public:
        explicit DisplayException(char const* message) noexcept;
        //virtual char const* what() const noexcept;
    };
};


#endif //TREMA_DISPLAYEXCEPTION_H
