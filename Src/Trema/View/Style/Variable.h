#ifndef TREMA_VARIABLE_H
#define TREMA_VARIABLE_H

#include <string>
#include <memory>
#include <cstring>
#include "TokenValue.h"

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
        Variable(TokenValue value, VariableType type);
        Variable(const Variable&) = delete;
        Variable& operator=(const Variable&) = delete;
        ~Variable();

        TokenValue CopyValue() const;
        TokenValue CopyValue(TokenValue v) const;

        inline TokenValue GetValue() const { return m_value; }
        inline VariableType GetType() const { return m_type; }
        std::string GetIdentity() const;

        void DeleteValue();

        friend std::ostream& operator<<(std::ostream& os, const Variable& st);

    private:
        TokenValue m_value;
        VariableType m_type;
    };
}

#endif //TREMA_VARIABLE_H
