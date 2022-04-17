//
// Created by JajaFil on 4/9/2022.
//

#include <sstream>
#include <iostream>
#include "Token.h"
#include "../../Utils/StringExtensions.h"

namespace Trema::View
{
    Token::Token(TokenType tokenType, unsigned int position, unsigned int line, void* value) :
            m_tokenType(tokenType),
            m_position(position),
            m_line(line),
            m_value(value)
    {

    }

    std::string Token::GetIdentity() const
    {
        std::stringstream ss;
        ss << "<";
        switch(m_tokenType)
        {
            case T_LNUMBER:
                ss << "NUMBER ('" << *((int64_t*) m_value) << " - " << ToHex(*((int64_t*) m_value)) << "'):";
                break;
            case T_LFNUMBER:
                ss << "FLOAT_NUMBER ('" << *((double*) m_value) << "'):";
                break;
            case T_IDENTIFIER:
                ss << "IDENTIFIER ('" << ((char*)m_value) << "'):";
                break;
            case T_IDENTITY:
                ss << "IDENTITY ('#'):";
                break;
            case T_ENDINS:
                ss << "ENDINS (';'):";
                break;
            case T_LPAR:
                ss << "LPAR ('('):";
                break;
            case T_RPAR:
                ss << "RPAR (')'):";
                break;
            case T_LCURLY:
                ss << "LCURLY ('{'):";
                break;
            case T_RCURLY:
                ss << "RCURLY ('}'):";
                break;
            case T_PROPASSIGN:
                ss << "PROPASSIGN (':'):";
                break;
            case T_VARASSIGN:
                ss << "VARASSIGN ('='):";
                break;
            case T_LSTRING:
                ss << "LSTRING ('" << ((char*)m_value) << "'):";
                break;
            case T_LBOOL:
                ss << "LSTRING ('" << (*((bool*)m_value)) << "'):";
                break;
            case T_STOP:
                ss << "STOP:";
                break;
        }
        ss << GetPosition() << ">\n";
        auto str = ss.str();

        return str;
    }

    void Token::DeleteValue()
    {
        switch(m_tokenType)
        {
            case T_IDENTIFIER:
            case T_LSTRING:
                delete[] static_cast<char*>(m_value);
                break;
            case T_LNUMBER:
                delete static_cast<int64_t*>(m_value);
                break;
            case T_LFNUMBER:
                delete static_cast<double*>(m_value);
                break;
            case T_LBOOL:
                delete static_cast<bool*>(m_value);
                break;
            default:
                break;
        }
    }

    Token::~Token()
    {
        DeleteValue();
    }
}