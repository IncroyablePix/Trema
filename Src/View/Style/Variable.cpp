//
// Created by JajaFil on 4/2/2022.
//

#include <sstream>
#include "Variable.h"
#include "../Utils/StringExtensions.h"
#include <iomanip>

namespace Trema::View
{
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
}
