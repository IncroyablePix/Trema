//
// Created by JajaFil on 3/18/2022.
//

#ifndef TREMA_FILENOTFOUNDEXCEPTION_H
#define TREMA_FILENOTFOUNDEXCEPTION_H

#include <stdexcept>

namespace Trema::View
{
    class FileNotFoundException : public std::runtime_error
    {
    public:
        explicit FileNotFoundException(char const* message) noexcept;
    };
}

#endif //TREMA_FILENOTFOUNDEXCEPTION_H
