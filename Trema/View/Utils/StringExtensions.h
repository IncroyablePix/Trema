//
// Created by JajaFil on 3/4/2022.
//

#ifndef TREMA_STRINGEXTENSIONS_H
#define TREMA_STRINGEXTENSIONS_H

#include <string>
#include <sstream>
#include <iomanip>

namespace Trema::View
{
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
#endif //TREMA_STRINGEXTENSIONS_H
