//
// Created by JajaFil on 4/2/2022.
//

#include <sstream>
#include "Variable.h"
#include "../Utils/StringExtensions.h"
#include <iomanip>
#include <iostream>

namespace Trema::View
{
    Variable::Variable(TokenValue value, VariableType type) :
    m_value(value),
    m_type(type)
    {
    }

    void Variable::DeleteValue()
    {
        switch(m_type)
        {
            case TYPE_STR:
                delete[] m_value.String;
                break;
            case TYPE_NUM:
                delete m_value.Integer;
                break;
            case TYPE_FLOAT:
                delete m_value.Float;
                break;
            case TYPE_BOOL:
                delete m_value.Boolean;
                break;
            default:
                break;
        }
    }

    std::string Variable::GetIdentity() const
    {
        std::stringstream ss;

        switch(GetType())
        {
            case TYPE_STR:
                ss << (char*)(m_value.String);
                break;
            case TYPE_NUM:
                ss << *((int64_t*)(m_value.Integer)) << " - " << ToHex(*((int64_t*)(m_value.Integer)));
                break;
            case TYPE_FLOAT:
                ss << *((double*)(m_value.Float));
                break;
            case TYPE_BOOL:
                ss << *((bool*)(m_value.Boolean));
                break;
        }

        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Variable &st)
    {
        os << st.GetIdentity();
        return os;
    }

    Variable::~Variable()
    {
        DeleteValue();
    }

    TokenValue Variable::CopyValue() const
    {
        return CopyValue(m_value);
    }

    TokenValue Variable::CopyValue(TokenValue toCopy) const
    {
        TokenValue value { };

        switch(GetType())
        {
            case TYPE_STR:
            {
                auto len = strlen(toCopy.String);
                auto *v = new char[len];
                strncpy((char *) v, toCopy.String, len);
                value.String = v;
                break;
            }
            case TYPE_NUM:
            {
                auto *v = new int64_t;
                *((int64_t *) v) = *(toCopy.Integer);
                value.Integer = v;
                break;
            }
            case TYPE_FLOAT:
            {
                auto *v = new double;
                *((double *) v) = *(toCopy.Float);
                value.Float = v;
                break;
            }
            case TYPE_BOOL:
            {
                auto *v = new bool;
                *((bool *) v) = *(toCopy.Boolean);
                value.Boolean = v;
                break;
            }
        }

        return value;
    }
}
