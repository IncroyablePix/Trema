//
// Created by JajaFil on 3/2/2022.
//

#ifndef TREMA_IPOPUPCOMPONENT_H
#define TREMA_IPOPUPCOMPONENT_H

#include <memory>
#include "IGuiElement.h"

namespace Trema::View
{
    class IPopupComponent : public IGuiElement
    {
    public:
        IPopupComponent(std::string name);
    };
}

#endif //TREMA_IPOPUPCOMPONENT_H
