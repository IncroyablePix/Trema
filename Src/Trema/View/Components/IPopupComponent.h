//
// Created by JajaFil on 3/2/2022.
//

#ifndef TREMA_IPOPUPCOMPONENT_H
#define TREMA_IPOPUPCOMPONENT_H

#include <memory>
#include "GuiElement.h"

namespace Trema::View
{
#include <memory>

    class IPopupComponent : public GuiElement
    {
    public:
        IPopupComponent(std::string name);
        virtual ~IPopupComponent() = default;
    };

    template<class T>
    concept PopupAsBase = std::is_base_of_v<IPopupComponent, T>;
}

#endif //TREMA_IPOPUPCOMPONENT_H
