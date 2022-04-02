//
// Created by JajaFil on 4/2/2022.
//

#ifndef TREMA_VARIABLE_H
#define TREMA_VARIABLE_H

#include <string>
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
        std::string GetIdentity() const;


    private:
        void* m_value;
        VariableType m_type;
    };
}

#endif //TREMA_VARIABLE_H
