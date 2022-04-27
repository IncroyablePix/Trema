//
// Created by JajaFil on 2/13/2022.
//

#include "ILayout.h"

namespace Trema::View
{
    ILayout::ILayout(std::string name) :
        IGuiElement(nullptr, std::move(name))
    {

    }
}