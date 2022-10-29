//
// Created by JajaFil on 3/19/2022.
//

#ifndef TREMA_SYMBOLTABLE_H
#define TREMA_SYMBOLTABLE_H


#include <unordered_map>
#include <memory>
#include <sstream>
#include "Variable.h"

namespace Trema::View
{
    class SymbolTable : public std::enable_shared_from_this<SymbolTable>
    {
    public:
        SymbolTable();
        SymbolTable(const SymbolTable& st);
        SymbolTable& operator=(const SymbolTable&) = delete;

        template<typename T> void SetVariable(const std::string &name, TokenValue value)
        {
            if(std::is_same<T, double>::value)
            {
                m_variables[name] = std::make_shared<Variable>(value, TYPE_FLOAT);
            }
            else if(std::is_same<T, int64_t>::value)
            {
                m_variables[name] = std::make_shared<Variable>(value, TYPE_NUM);
            }
            else if(std::is_same<T, char>::value)
            {
                m_variables[name] = std::make_shared<Variable>(value, TYPE_STR);
            }
            else if(std::is_same<T, bool>::value)
            {
                m_variables[name] = std::make_shared<Variable>(value, TYPE_BOOL);
            }
            else
            {
                throw std::runtime_error("Invalid variable type");
            }
        }

        bool HasVariable(const std::string &name) { return m_variables.find(name) != m_variables.end(); }
        std::shared_ptr<Variable> GetVariable(const std::string& name) { return m_variables[name]; }
        void Append(const SymbolTable &st);

        friend std::ostream& operator<<(std::ostream& os, const SymbolTable& st);

        auto begin() { return m_variables.begin(); }
        auto end() { return m_variables.end(); }

    private:
        std::unordered_map<std::string, std::shared_ptr<Variable>> m_variables;
    };
}

#endif //TREMA_SYMBOLTABLE_H
