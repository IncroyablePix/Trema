//
// Created by JajaFil on 3/2/2022.
//

#include "IPopupComponent.h"

#include <utility>

namespace Trema::View
{
    IPopupComponent::IPopupComponent(std::string name) :
            GuiElement(nullptr, std::move(name))
    {

    }
}