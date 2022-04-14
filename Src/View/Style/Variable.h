//
// Created by JajaFil on 4/2/2022.
//

#ifndef TREMA_VARIABLE_H
#define TREMA_VARIABLE_H

#include <string>
#include <memory>
#include <cstring>

namespace Trema::View
{
    enum VariableType
    {
        TYPE_STR,
        TYPE_NUM,
        TYPE_FLOAT,
        TYPE_BOOL
    };

    class Variable : public std::enable_shared_from_this<Variable>
    {
    public:
        Variable(void* value, VariableType type);
        ~Variable();

        inline void* CopyValue() const
        {
            void* v;
            switch(GetType())
            {
                case TYPE_STR:
                    v = new char[strlen((char*)m_value)];
                    strcpy((char*)v, (char*)m_value);
                    break;
                case TYPE_NUM:
                    v = new int64_t;
                    *((int64_t*)v) = *((int64_t*)m_value);
                    break;
                case TYPE_FLOAT:
                    v = new double;
                    *((double*)v) = *((double*)m_value);
                    break;
                case TYPE_BOOL:
                    v = new bool;
                    *((bool*)v) = *((bool*)m_value);
                    break;
            }

            return v;
        }

        template<typename T>
        inline T GetValue() const { return (T) m_value; }
        template<typename T>
        inline T GetPtrValue() const { return *(reinterpret_cast<T*>(m_value)); }

        inline void* GetValue() const { return m_value; }
        inline VariableType GetType() const { return m_type; }
        std::string GetIdentity() const;

        void DeleteValue();

        friend std::ostream& operator<<(std::ostream& os, const Variable& st);

    private:
        void* m_value;
        VariableType m_type;
    };
}

#endif //TREMA_VARIABLE_H
