//
// Created by JajaFil on 10/29/2022.
//

#include "StringConversion.h"

namespace Trema::Utils
{
    float StrToFloat(const std::string &str)
    {
        float val = 0;
        std::stringstream ss;
        ss << str;
        ss >> val;

        return val;
    }

    int StrToInt(const std::string &str)
    {
        int integer = 0;
        std::stringstream ss;
        ss << str;
        ss >> integer;

        return integer;
    }

    bool StrToBool(const std::string_view &str)
    {
        return str == "true";
    }

    bool IsFloat(const std::string& myString)
    {
        std::istringstream iss(myString);
        float f;
        iss >> std::noskipws >> f;
        return iss.eof() && !iss.fail();
    }
}