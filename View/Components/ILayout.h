//
// Created by JajaFil on 2/13/2022.
//

#ifndef TREMA_ILAYOUT_H
#define TREMA_ILAYOUT_H

#include "IGuiElement.h"

namespace Trema::View
{
    class ILayout : public IGuiElement
    {
    public:
        ILayout(std::string name);
    };
}

#endif //TREMA_ILAYOUT_H