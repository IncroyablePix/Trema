//
// Created by JajaFil on 3/16/2022.
//

#ifndef TREMA_TOKENIZER_H
#define TREMA_TOKENIZER_H


#include <string>
#include <memory>
#include <deque>

namespace Trema::View
{
    typedef enum
    {
        T_LNUMBER = 1, // number
        T_IDENTIFIER = 2, // property name, applier, variable
        T_IDENTITY = 3, // #
        T_ENDINS = 4, // ;
        T_LPAR = 5, // (
        T_RPAR = 6, // )
        T_LCURLY = 7, // {
        T_RCURLY = 8, // }
        T_PROPASSIGN = 9, // :
        T_VARASSIGN = 10, // =
        T_LSTRING = 11, // " " || ' '
        T_LBOOL = 12,
        T_STOP = -1 // End of expression
    } TokenType;

    class Token
    {
    public:
        Token(TokenType tokenType, unsigned int position, void* value);
        inline unsigned int GetPosition() const { return m_position; }
        inline TokenType GetTokenType() const { return m_tokenType; }
        inline void* GetValue() const { return m_value; }
        std::string GetIdentity() const;

    protected:
        TokenType m_tokenType;
        void* m_value;
        unsigned int m_position;
    };

    class Tokenizer
    {
    public:
        explicit Tokenizer(const std::string& code);
        std::unique_ptr<Token> GetNextToken();
        inline bool Empty() const { return m_tokens.empty(); }
    private:

        TokenType m_lastType;
        std::deque<std::unique_ptr<Token>> m_tokens;
        const char* m_code;
        unsigned int m_cursor;

        unsigned int m_line;
        unsigned int m_linePos;

        std::unique_ptr<Token> ParseToken();
    };
}

#endif //TREMA_TOKENIZER_H
