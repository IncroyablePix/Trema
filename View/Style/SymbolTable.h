//
// Created by JajaFil on 3/19/2022.
//

#ifndef TREMA_SYMBOLTABLE_H
#define TREMA_SYMBOLTABLE_H


#include <unordered_map>
#include <memory>

namespace Trema::View
{
    enum VariableType
    {
        TYPE_STR,
        TYPE_NUM,
        TYPE_BOOL
    };

    class Variable : public std::enable_shared_from_this<Variable>
    {
    public:
        Variable(void* value, VariableType type) : m_value(value), m_type(type) { }
        ~Variable()
        {
            switch(GetType())
            {
                case TYPE_STR:
                    delete static_cast<char*>(m_value);
                    break;
                case TYPE_NUM:
                    delete static_cast<double*>(m_value);
                    break;
                case TYPE_BOOL:
                    delete static_cast<bool*>(m_value);
                    break;
            }
        }

        inline void* GetValue() const { return m_value; }
        inline VariableType GetType() const { return m_type; }

    private:
        void* m_value;
        VariableType m_type;
    };

    class SymbolTable
    {
    public:
        SymbolTable();
        template<typename T> void SetVariable(const std::string &name, T* value)
        {
            if(std::is_same<T, double>::value)
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

    private:
        std::unordered_map<std::string, std::shared_ptr<Variable>> m_variables;
    };
}

#endif //TREMA_SYMBOLTABLE_H
