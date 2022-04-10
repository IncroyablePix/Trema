//
// Created by JajaFil on 3/16/2022.
//

#ifndef TREMA_TOKENIZER_H
#define TREMA_TOKENIZER_H


#include <string>
#include <memory>
#include <deque>
#include <vector>
#include "../CompilationMistake.h"
#include "Token.h"
#include "ITokenizer.h"

namespace Trema::View
{
    class Tokenizer : ITokenizer
    {
    public:
        explicit Tokenizer(const std::string& code, std::vector<CompilationMistake> &mistakes);
        std::unique_ptr<Token> GetNextToken() override;
        inline bool Empty() const override  { return m_tokens.empty(); }
    private:

        TokenType m_lastType;
        std::deque<std::unique_ptr<Token>> m_tokens;
        const char* m_code;
        unsigned int m_cursor;

        unsigned int m_line;
        unsigned int m_linePos;

        std::unique_ptr<Token> ParseToken(std::vector<CompilationMistake> &mistakes);
    };
}

#endif //TREMA_TOKENIZER_H
