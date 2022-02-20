//
// Created by JajaFil on 2/19/2022.
//

#ifndef TREMA_PARSINGEXCEPTION_H
#define TREMA_PARSINGEXCEPTION_H

#include <stdexcept>

namespace Trema::View
{
    class ParsingException : public std::runtime_error
    {
    public:
        explicit ParsingException(char const* const message) noexcept;
        //virtual char const* what() const noexcept;
    };
}


#endif //TREMA_PARSINGEXCEPTION_H
