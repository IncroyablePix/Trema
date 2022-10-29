//
// Created by JajaFil on 10/29/2022.
//

#ifndef TREMA_STRINGCONVERSION_H
#define TREMA_STRINGCONVERSION_H

#include <string>
#include <sstream>
#include <iomanip>

namespace Trema::Utils
{
    int StrToInt(const std::string& str);
    bool StrToBool(const std::string_view &str);
    float StrToFloat(const std::string &str);

    bool IsFloat(const std::string &myString);

    template<typename T>
    std::string ToHex(T i)
    {
        std::stringstream stream;
        stream << "0x"
               << std::setfill('0') << std::setw(sizeof(T) * 2)
               << std::hex << i;
        return stream.str();
    }
}


#endif //TREMA_STRINGCONVERSION_H
