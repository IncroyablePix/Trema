#ifndef TREMA_IELEMENTSLIBRARY_H
#define TREMA_IELEMENTSLIBRARY_H

#include "ViewParser.h"

namespace Trema::View
{
    class IElementsLibrary
    {
    public:
        virtual void AddElements(ViewParser &viewParser) = 0;
    };
}

#endif //TREMA_IELEMENTSLIBRARY_H
