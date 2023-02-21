#ifndef TREMA_PARSINGEXCEPTION_H
#define TREMA_PARSINGEXCEPTION_H

#include <stdexcept>

namespace Trema::View
{
    class ParsingException : public std::runtime_error
    {
    public:
        explicit ParsingException(char const* message) noexcept;
    };
}


#endif //TREMA_PARSINGEXCEPTION_H
