//
// Created by JajaFil on 3/29/2022.
//

#ifndef TREMA_LAYOUTEXCEPTION_H
#define TREMA_LAYOUTEXCEPTION_H


#include <stdexcept>

namespace Trema::View
{
    class LayoutException : public std::runtime_error
    {
    public:
        explicit LayoutException(char const* message) noexcept;
    };
}

#endif //TREMA_LAYOUTEXCEPTION_H
