//
// Created by Benjam on 11/7/2022.
//

#ifndef TREMA_MISSINGATTRIBUTEEXCEPTION_H
#define TREMA_MISSINGATTRIBUTEEXCEPTION_H

#include <stdexcept>

namespace Trema::View
{
    class MissingAttributeException : public std::runtime_error
    {
    public:
        explicit MissingAttributeException(char const* message) noexcept;
    };
}



#endif //TREMA_MISSINGATTRIBUTEEXCEPTION_H
