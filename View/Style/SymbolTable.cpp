//
// Created by JajaFil on 3/19/2022.
//

#include <algorithm>
#include "SymbolTable.h"

namespace Trema::View
{
    SymbolTable::SymbolTable()
    {

    }

    std::ostream &operator<<(std::ostream &os, const SymbolTable &st)
    {
        for(const auto& [key, val] : st.m_variables)
        {
            os << "\t[" << key << ":" << val->GetIdentity() << "]\n";
        }

        os << std::endl;
        return os;
    }

    SymbolTable::SymbolTable(const SymbolTable& st) : m_variables(st.m_variables)
    {

    }

    void SymbolTable::Append(const SymbolTable &st)
    {
        for(const auto& [name, val] : st.m_variables)
            m_variables[name] = val;
    }
}