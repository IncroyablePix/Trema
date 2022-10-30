//
// Created by JajaFil on 4/5/2022.
//

#include "CompilationMistake.h"
#include <iostream>

namespace Trema::View
{
    std::ostream &operator<<(std::ostream &os, const CompilationMistake &m)
    {
        switch(m.Code)
        {
            case UnknownError:
                os << "Unknown error (" << ((unsigned short)m.Code)  << " | "<< m.Line << ":" << m.Position << ")";
                break;

            case UnknownToken:
                os << "Unknown token (" << ((unsigned short)m.Code)  << " | "<< m.Line << ":" << m.Position << "): " << m.Extra;
                break;
            case UnfinishedString:
                os << "Unfinished string (" << ((unsigned short)m.Code)  << " | "<< m.Line << ":" << m.Position << "): " << m.Extra;
                break;

            case UndefinedSymbol:
                os << "Undefined symbol (" << ((unsigned short)m.Code)  << " | "<< m.Line << ":" << m.Position << "): " << m.Extra;
                break;
            case UnexpectedToken:
                os << "Unexpected token (" << ((unsigned short)m.Code)  << " | "<< m.Line << ":" << m.Position << "): " << m.Extra;
                break;

            case ElementNotFound:
                os << "Element not found (" << ((unsigned short)m.Code)  << " | "<< m.Line << ":" << m.Position << "): " << m.Extra;
                break;
            case MissingAttribute:
                os << "Missing attribute (" << ((unsigned short)m.Code)  << " | "<< m.Line << ":" << m.Position << "): " << m.Extra;
                break;
            case MisplacedElement:
                os << "Misplaced element (" << ((unsigned short)m.Code)  << " | "<< m.Line << ":" << m.Position << "): " << m.Extra;
                break;
        }
        return os;
    }
}