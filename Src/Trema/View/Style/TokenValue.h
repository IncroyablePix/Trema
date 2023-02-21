#ifndef TREMA_PROJECT_TOKENVALUE_H
#define TREMA_PROJECT_TOKENVALUE_H

#include <cstdint>
#include <cstring>
#include <type_traits>

namespace Trema::View
{
    union TokenValue
    {
        double *Float;
        int64_t *Integer;
        bool *Boolean;
        char *String;

        template<typename T>
        inline TokenValue Clone() const
        {
            TokenValue value { };

            if(std::is_same<T, char*>::value)
            {
                auto len = strlen(String);
                auto *v = new char[len + 1];
                strcpy((char *) v, String);
                v[len] = '\0';
                value.String = v;
            }
            else if(std::is_same<T, int64_t>::value)
            {
                auto *v = new int64_t;
                *((int64_t *) v) = *(Integer);
                value.Integer = v;
            }
            else if(std::is_same<T, double>::value)
            {
                auto *v = new double;
                *((double *) v) = *(Float);
                value.Float = v;
            }
            else if(std::is_same<T, bool>::value)
            {
                auto *v = new bool;
                *((bool *) v) = *(Boolean);
                value.Boolean = v;
            }

            return value;
        }
    };
}

#endif //TREMA_PROJECT_TOKENVALUE_H
