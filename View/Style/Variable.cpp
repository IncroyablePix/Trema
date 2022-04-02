//
// Created by JajaFil on 4/2/2022.
//

#include <sstream>
#include "Variable.h"

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
                ss << *((double*)(m_value));
                break;
            case TYPE_BOOL:
                ss << *((bool*)(m_value));
                break;
        }

        return ss.str();
    }
}
