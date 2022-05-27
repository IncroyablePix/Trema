//
// Created by JajaFil on 5/22/2022.
//

#ifndef TREMA_PROJECT_NOACTIVITYBUILDEREXCEPTION_H
#define TREMA_PROJECT_NOACTIVITYBUILDEREXCEPTION_H

#include <stdexcept>

namespace Trema::View
{
class NoActivityBuilderException : public std::runtime_error
    {
    public:
        NoActivityBuilderException(char const* message);
    };
}

#endif //TREMA_PROJECT_NOACTIVITYBUILDEREXCEPTION_H
