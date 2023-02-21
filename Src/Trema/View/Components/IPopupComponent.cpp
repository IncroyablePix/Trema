#include "IPopupComponent.h"

#include <utility>

namespace Trema::View
{
    IPopupComponent::IPopupComponent(std::string name) :
            GuiElement(nullptr, std::move(name))
    {

    }
}