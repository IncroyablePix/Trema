//
// Created by JajaFil on 4/9/2022.
//

#ifndef TREMA_TOKEN_H
#define TREMA_TOKEN_H

#include <string>
#include <ostream>
#include "../TokenValue.h"

namespace Trema::View
{
    enum TokenType
    {
        T_LFNUMBER = 1, // number
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
        T_LNUMBER = 12, // number
        T_LBOOL = 13,
        T_COMMENT = 14, // /* */
        T_OPERATOR = 15, // + - * / %
        T_STOP = -1 // End of expression
    };

    class Token
    {
    public:
        Token(TokenType tokenType, unsigned int position, unsigned int line, TokenValue value);
        ~Token();
        inline unsigned int GetPosition() const { return m_position; }
        inline unsigned int GetLine() const { return m_line; }
        inline TokenType GetTokenType() const { return m_tokenType; }
        inline TokenValue GetValue() const { return m_value; }

        TokenValue CopyValue() const;
        TokenValue CopyValue(TokenValue v) const;

        std::string GetIdentity() const;
        void DeleteValue();

        friend std::ostream &operator<<(std::ostream &os, const Token &token);

    protected:
        TokenType m_tokenType;
        TokenValue m_value;
        unsigned int m_position;
        unsigned int m_line;
    };
}

#endif //TREMA_TOKEN_H
