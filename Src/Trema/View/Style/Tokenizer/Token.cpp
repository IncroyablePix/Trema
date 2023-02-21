#include <sstream>
#include <iostream>
#include "Token.h"
#include "../../../Utils/StringConversion.h"

namespace Trema::View
{
    Token::Token(TokenType tokenType, unsigned int position, unsigned int line, TokenValue value) :
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
                ss << "NUMBER ('" << *m_value.Integer << " - " << Utils::ToHex(*m_value.Integer) << "'):";
                break;
            case T_LFNUMBER:
                ss << "FLOAT_NUMBER ('" << *m_value.Float << "'):";
                break;
            case T_IDENTIFIER:
                ss << "IDENTIFIER ('" << m_value.String << "'):";
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
                ss << "LSTRING ('" << m_value.String << "'):";
                break;
            case T_LBOOL:
                ss << "LBOOL ('" << (*m_value.Boolean ? "true" : "false") << "'):";
                break;
            case T_COMMENT:
                ss << "COMMENT('" << m_value.String << "'):";
                break;
            case T_STOP:
                ss << "STOP:";
                break;
            case T_OPERATOR:
                ss << "OPERATOR ('" << m_value.String << "'):";
                break;
        }
        ss << GetPosition() << ">\n";
        auto str = ss.str();

        return str;
    }

    std::ostream &operator<<(std::ostream &os, const Token &token)
    {
        os << token.GetIdentity();
        return os;
    }

    void Token::DeleteValue()
    {
        switch(m_tokenType)
        {
            case T_IDENTIFIER:
            case T_LSTRING:
                delete[] m_value.String;
                break;
            case T_LNUMBER:
                delete m_value.Integer;
                break;
            case T_LFNUMBER:
                delete m_value.Float;
                break;
            case T_LBOOL:
                delete m_value.Boolean;
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