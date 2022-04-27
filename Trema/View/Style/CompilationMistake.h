//
// Created by JajaFil on 4/5/2022.
//

#ifndef TREMA_COMPILATIONMISTAKE_H
#define TREMA_COMPILATIONMISTAKE_H


#include <string>

namespace Trema::View
{
    enum ErrorCode : unsigned short
    {
        // Unknown
        UnknownError = 0,

        // Tokenizer
        UnknownToken = 1001,
        UnfinishedString = 1002,

        // Parsing
        UndefinedSymbol = 2001,
        UnexpectedToken = 2002
    };

    struct CompilationMistake
    {
        unsigned int Line { 0 };
        unsigned int Position { 0 };
        bool Fatal { false };
        ErrorCode Code { UnknownError };
        std::string Extra;

        friend std::ostream& operator<<(std::ostream& os, const CompilationMistake& st);
    };
}

#endif //TREMA_COMPILATIONMISTAKE_H
