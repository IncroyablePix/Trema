//
// Created by JajaFil on 4/9/2022.
//

#ifndef TREMA_ITOKENIZER_H
#define TREMA_ITOKENIZER_H

#include <memory>
#include "Token.h"

namespace Trema::View
{
    class ITokenizer
    {
    public:
        virtual ~ITokenizer() = default;
        virtual std::unique_ptr<Token> GetNextToken() = 0;
        virtual bool Empty() const = 0;
        virtual size_t Size() const = 0;
    };
}

#endif //TREMA_ITOKENIZER_H
