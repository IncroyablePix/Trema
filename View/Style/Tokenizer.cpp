//
// Created by JajaFil on 3/16/2022.
//

#include <cstring>
#include <sstream>
#include "Tokenizer.h"
#include "../Exceptions/ParsingException.h"

namespace Trema::View
{
    bool IsNumber(const char* string, TokenType lastType)
    {
        if(string[0] == '\0')
            return false;

        if(std::isdigit(string[0]))
            return true;

        if(string[1] == '\0')
            return false;

        if(string[0] == '.' && std::isdigit(string[1]))
            return true;

        if((lastType == T_LPAR || lastType == T_VARASSIGN || lastType == T_PROPASSIGN ) &&
            string[0] == '-' && std::isdigit(string[1]))
            return true;

        if(string[2] == '\0')
            return false;

        if((lastType == T_LPAR || lastType == T_PROPASSIGN || lastType == T_VARASSIGN) &&
            string[0] == '-' &&
            string[1] == '.' &&
            std::isdigit(string[2]))
            return true;

        if((string[0] && (string[1] == 'x' || string[1] =='X')))
            return true;

        return false;
    }

    Tokenizer::Tokenizer(const std::string& code) :
        m_code(code.c_str()),
        m_cursor(0),
        m_line(1),
        m_linePos(1),
        m_lastType(T_LPAR)
    {
        while(m_lastType != T_STOP)
        {
            m_tokens.push_back(std::move(ParseToken()));
        }
    }

    std::unique_ptr<Token> Tokenizer::ParseToken()
    {
        unsigned int pos = m_cursor;

        // ignoring white spaces
        while(std::isspace(m_code[pos]))
        {
            if(m_code[pos] == '\n')
            {
                m_line ++;
                m_linePos = 0;
            }

            m_linePos ++;
            pos ++;
        }

        m_cursor = pos;

        char c, *symbolPtr;
        unsigned int l;
        double *valuePtr;

        while((c = m_code[pos]) != '\0')
        {
            if(c == ';')
            {
                m_lastType = T_ENDINS;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_ENDINS, m_cursor, nullptr));
                return t;
            }

            else if(c == '(')
            {
                m_lastType = T_LPAR;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_LPAR, m_cursor, nullptr));
                return t;
            }

            else if(c == ')')
            {
                m_lastType = T_RPAR;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_RPAR, m_cursor, nullptr));
                return t;
            }

            else if(c == '{')
            {
                m_lastType = T_LCURLY;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_LCURLY, m_cursor, nullptr));
                return t;
            }

            else if(c == '}')
            {
                m_lastType = T_RCURLY;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_RCURLY, m_cursor, nullptr));
                return t;
            }

            else if(c == ':')
            {
                m_lastType = T_PROPASSIGN;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_PROPASSIGN, m_cursor, nullptr));
                return t;
            }

            else if(c == '=')
            {
                m_lastType = T_VARASSIGN;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_VARASSIGN, m_cursor, nullptr));
                return t;
            }

            else if(c == '#')
            {
                m_lastType = T_IDENTITY;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_IDENTITY, m_cursor, nullptr));
                return t;
            }

            // *
            else if (c == '*')
            {
                m_lastType = T_IDENTIFIER;
                m_cursor = pos + 1;
                m_linePos ++;

                symbolPtr = new char[2];
                strcpy(symbolPtr, "*");

                auto t = std::move(std::make_unique<Token>(T_IDENTIFIER, m_cursor, symbolPtr));
                return t;
            }

            else if (c == '\'' || c == '"')
            {
                l = pos + 1;

                while(m_code[l] != '\0' && m_code[l] != c && m_code[l] != '\n')
                {
                    l ++;

                    if(m_code[l] == '\0' || m_code[l] == '\n')
                    {
                        std::stringstream ss;
                        ss << "Unfinished string on line " << m_line;
                        throw ParsingException(ss.str().c_str());
                    }
                }
                l -= pos;
                symbolPtr = new char[l - 1];
                strncpy(symbolPtr, m_code + pos + 1, l - 1);
                symbolPtr[l] = '\0';

                auto t = std::move(std::make_unique<Token>(T_LSTRING, m_cursor, symbolPtr));
                m_cursor = pos + l + 1;
                m_linePos += l + 1;
                m_lastType = T_LSTRING;

                return t;
            }

            else if(IsNumber(m_code + pos, m_lastType))
            {
                valuePtr = new double;
                *valuePtr = strtod(m_code + pos, &symbolPtr);

                auto size = (unsigned int) (symbolPtr - (m_code + pos));
                pos += size;
                m_linePos += size;

                auto t = std::move(std::make_unique<Token>(T_LNUMBER, m_cursor, valuePtr));
                m_cursor = pos;
                m_lastType = T_LNUMBER;
                return t;
            }

            else if(std::isalpha(c))
            {
                l = pos + 1;

                while(m_code[l] != '\0' && (std::isalpha(m_code[l]) || std::isdigit(m_code[l]) || m_code[l] == '_'))
                {
                    l ++;
                }

                l -= pos;
                symbolPtr = new char[l];
                strncpy(symbolPtr, m_code + pos, l);
                symbolPtr[l] = '\0';

                auto t = std::move(std::make_unique<Token>(T_IDENTIFIER, m_cursor, symbolPtr));
                m_cursor = pos + l;
                m_linePos += l;
                m_lastType = T_IDENTIFIER;

                return t;
            }

            else
            {
                std::stringstream ss;
                ss << "Unknown token '" << c << "' on " << m_line << ":" << m_linePos;
                throw ParsingException(ss.str().c_str());
            }
        }

        m_cursor = pos + 1;
        m_lastType = T_STOP;
        auto t = std::move(std::make_unique<Token>(T_STOP, m_cursor, nullptr));
        return t;
    }

    std::unique_ptr<Token> Tokenizer::GetNextToken()
    {
        auto t = std::move(m_tokens.front());
        m_tokens.pop_front();

        return t;
    }

    Token::Token(TokenType tokenType, unsigned int position, void* value) :
        m_tokenType(tokenType),
        m_position(position),
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
                ss << "NUMBER ('" << *((double*) m_value) << "'):";
                break;
            case T_IDENTIFIER:
                ss << "IDENTIFIER ('" << (std::string((char*)m_value)) << "'):";
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
                ss << "LSTRING ('" << (std::string((char*)m_value)) << "'):";
                break;
            case T_LBOOL:
                ss << "LSTRING ('" << (std::string((char*)m_value)) << "'):";
                break;
            case T_STOP:
                ss << "STOP:";
                break;
        }
        ss << GetPosition() << ">\n";
        auto str = ss.str();

        return str;
    }
}