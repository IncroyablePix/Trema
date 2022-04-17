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
    Variable::Variable(void *value, VariableType type) : m_type(type), m_value(nullptr)
    {
        switch(type)
        {
            case TYPE_STR:
            {
                auto len = strlen((const char *) value);
                m_value = new char[len];

                strcpy((char *) m_value, (const char *) value);
            }
            break;
            case TYPE_NUM:
                m_value = new int64_t(*((int64_t*)(value)));
                break;
            case TYPE_FLOAT:
                m_value = new double(*((double*)(value)));
                break;
            case TYPE_BOOL:
                m_value = new bool(*((bool*)(value)));
                break;
        }
    }

    void Variable::DeleteValue()
    {
        switch(m_type)
        {
            case TYPE_STR:
                delete[] static_cast<char*>(m_value);
                break;
            case TYPE_NUM:
                delete static_cast<int64_t*>(m_value);
                break;
            case TYPE_FLOAT:
                delete static_cast<double*>(m_value);
                break;
            case TYPE_BOOL:
                delete static_cast<bool*>(m_value);
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
                ss << (char*)(m_value);
                break;
            case TYPE_NUM:
                ss << *((int64_t*)(m_value)) << " - " << ToHex(*((int64_t*)(m_value)));
                break;
            case TYPE_FLOAT:
                ss << *((double*)(m_value));
                break;
            case TYPE_BOOL:
                ss << *((bool*)(m_value));
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
}
