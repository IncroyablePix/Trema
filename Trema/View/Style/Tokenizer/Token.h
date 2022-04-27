//
// Created by JajaFil on 4/9/2022.
//

#ifndef TREMA_TOKEN_H
#define TREMA_TOKEN_H

#include <string>

namespace Trema::View
{    typedef enum
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
        T_STOP = -1 // End of expression
    } TokenType;

    class Token
    {
    public:
        Token(TokenType tokenType, unsigned int position, unsigned int line, void* value);
        ~Token();
        inline unsigned int GetPosition() const { return m_position; }
        inline unsigned int GetLine() const { return m_line; }
        inline TokenType GetTokenType() const { return m_tokenType; }
        inline void* GetValue() const { return m_value; }
        std::string GetIdentity() const;
        void DeleteValue();

    protected:
        TokenType m_tokenType;
        void* m_value;
        unsigned int m_position;
        unsigned int m_line;
    };
}

#endif //TREMA_TOKEN_H
