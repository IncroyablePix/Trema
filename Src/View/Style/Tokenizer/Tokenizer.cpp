//
// Created by JajaFil on 3/16/2022.
//

#include <cstring>
#include <sstream>
#include <cmath>
#include "Tokenizer.h"
#include "../../Exceptions/ParsingException.h"
#include "../../Utils/StringExtensions.h"

namespace Trema::View
{
    bool IsFloatNumber(const char* string, TokenType lastType)
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

    bool IsHexNumber(const char* string, size_t size)
    {
        std::string s(string, size);

        return (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) &&
            s.size() > 2 &&
            s.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos;
    }

    long long IntFromHex(const char* string, size_t size)
    {
        auto hexString = std::string(string + 2, size - 2);
        auto val = std::stoll(hexString, nullptr, 16);

        return val;
    }

    Tokenizer::Tokenizer(const std::string& code, std::vector<CompilationMistake> &mistakes) :
        m_code(code.c_str()),
        m_cursor(0),
        m_line(1),
        m_linePos(1),
        m_lastType(T_LPAR)
    {
        while(m_lastType != T_STOP)
        {
            m_tokens.push_back(std::move(ParseToken(mistakes)));
        }
    }

    std::unique_ptr<Token> Tokenizer::ParseToken(std::vector<CompilationMistake> &mistakes)
    {
        unsigned int pos = m_cursor;

        std::locale loc("C");
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
        double *fValuePtr;
        int64_t *valuePtr;

        while((c = m_code[pos]) != '\0')
        {
            if(c == ';')
            {
                m_lastType = T_ENDINS;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_ENDINS, m_linePos, m_line, nullptr));
                return t;
            }

            else if(c == '(')
            {
                m_lastType = T_LPAR;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_LPAR, m_linePos, m_line, nullptr));
                return t;
            }

            else if(c == ')')
            {
                m_lastType = T_RPAR;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_RPAR, m_linePos, m_line, nullptr));
                return t;
            }

            else if(c == '{')
            {
                m_lastType = T_LCURLY;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_LCURLY, m_linePos, m_line, nullptr));
                return t;
            }

            else if(c == '}')
            {
                m_lastType = T_RCURLY;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_RCURLY, m_linePos, m_line, nullptr));
                return t;
            }

            else if(c == ':')
            {
                m_lastType = T_PROPASSIGN;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_PROPASSIGN, m_linePos, m_line, nullptr));
                return t;
            }

            else if(c == '=')
            {
                m_lastType = T_VARASSIGN;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_VARASSIGN, m_linePos, m_line, nullptr));
                return t;
            }

            else if(c == '#')
            {
                m_lastType = T_IDENTITY;
                m_cursor = pos + 1;
                m_linePos ++;
                auto t = std::move(std::make_unique<Token>(T_IDENTITY, m_linePos, m_line, nullptr));
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

                auto t = std::move(std::make_unique<Token>(T_IDENTIFIER, m_linePos, m_line, symbolPtr));
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
                        mistakes.emplace_back(CompilationMistake { .Line = m_line, .Position = m_linePos, .Code = ErrorCode::UnfinishedString, .Extra = "" });
                        l --;
                        break;
                    }
                }
                l -= pos;
                symbolPtr = new char[l];
                strncpy(symbolPtr, m_code + pos + 1, l - 1);
                symbolPtr[l - 1] = '\0';

                auto t = std::move(std::make_unique<Token>(T_LSTRING, m_linePos, m_line, symbolPtr));
                m_cursor = pos + l + 1;
                m_linePos += l + 1;
                m_lastType = T_LSTRING;

                return t;
            }

            else if(IsFloatNumber(m_code + pos, m_lastType))
            {
                const char* offset = m_code + pos;
                double intPart, fractPart;
                fValuePtr = new double;
                *fValuePtr = strtod(offset, &symbolPtr);

                auto size = (unsigned int) (symbolPtr - (m_code + pos));
                pos += size;
                m_linePos += size;

                fractPart = modf(*fValuePtr, &intPart);
                if (fractPart == 0 || IsHexNumber(offset, size))
                {
                    valuePtr = new int64_t;

                    if(IsHexNumber(offset, size))
                        *valuePtr = IntFromHex(offset, size);
                    else
                        *valuePtr = (int)*fValuePtr;

                    auto t = std::move(std::make_unique<Token>(T_LNUMBER, m_linePos, m_line, valuePtr));
                    m_cursor = pos;
                    m_lastType = T_LNUMBER;
                    return t;
                }
                else
                {
                    auto t = std::move(std::make_unique<Token>(T_LFNUMBER, m_linePos, m_line, fValuePtr));
                    m_cursor = pos;
                    m_lastType = T_LFNUMBER;
                    return t;
                }
            }

            else if(std::isalpha(c, loc))
            {
                l = pos + 1;

                while(m_code[l] != '\0' && (std::isalpha(m_code[l], loc) || std::isdigit(m_code[l]) || m_code[l] == '_' || m_code[l] == '-'))
                {
                    l ++;
                }

                l -= pos;
                symbolPtr = new char[l];
                strncpy(symbolPtr, m_code + pos, l);
                symbolPtr[l] = '\0';

                auto t = std::move(std::make_unique<Token>(T_IDENTIFIER, m_linePos, m_line, symbolPtr));
                m_cursor = pos + l;
                m_linePos += l;
                m_lastType = T_IDENTIFIER;

                return t;
            }

            else
            {
                mistakes.emplace_back(CompilationMistake { .Line = m_line, .Position = m_linePos, .Code = ErrorCode::UnknownToken, .Extra = &""[c] });
                pos ++;
                m_cursor++;
                m_linePos ++;
            }
        }

        m_cursor = pos + 1;
        m_lastType = T_STOP;
        auto t = std::move(std::make_unique<Token>(T_STOP, m_linePos, m_line, nullptr));
        return t;
    }

    std::unique_ptr<Token> Tokenizer::GetNextToken()
    {
        auto t = std::move(m_tokens.front());
        m_tokens.pop_front();

        return t;
    }
}