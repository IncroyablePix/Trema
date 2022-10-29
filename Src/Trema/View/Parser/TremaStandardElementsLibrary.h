//
// Created by JajaFil on 10/29/2022.
//

#ifndef TREMA_TREMASTANDARDELEMENTSLIBRARY_H
#define TREMA_TREMASTANDARDELEMENTSLIBRARY_H


#include "IElementsLibrary.h"

namespace Trema::View
{
    class TremaStandardElementsLibrary : public IElementsLibrary
    {
    public:
        void AddElements(ViewParser &viewParser) override;
    };
}

#endif //TREMA_TREMASTANDARDELEMENTSLIBRARY_H
