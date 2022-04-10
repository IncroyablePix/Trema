//
// Created by JajaFil on 3/4/2022.
//

#include "StringExtensions.h"
#include <sstream>

namespace Trema::View
{
    bool IsFloat(const std::string& myString)
    {
        std::istringstream iss(myString);
        float f;
        iss >> std::noskipws >> f;
        return iss.eof() && !iss.fail();
    }
}