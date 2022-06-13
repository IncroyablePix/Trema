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
        Tokenizer(const Tokenizer&) = delete;
        Tokenizer& operator=(const Tokenizer&) = delete;
        ~Tokenizer() override = default;
        std::unique_ptr<Token> GetNextToken() override;
        inline bool Empty() const override  { return m_tokens.empty(); }
        inline size_t Size() const override { return m_tokens.size(); }
    private:

        TokenType m_lastType { T_LPAR };
        std::deque<std::unique_ptr<Token>> m_tokens;
        const char* m_code;
        unsigned int m_cursor { 0 };

        unsigned int m_line { 1 };
        unsigned int m_linePos { 1 };

        std::unique_ptr<Token> ParseToken(std::vector<CompilationMistake> &mistakes);
    };
}

#endif //TREMA_TOKENIZER_H
