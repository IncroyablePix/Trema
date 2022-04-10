//
// Created by JajaFil on 2/13/2022.
//

#include "IContainer.h"

#include <utility>

namespace Trema::View
{
    IContainer::IContainer(std::shared_ptr<IGuiElement> parent, std::string name) :
            IGuiElement(std::move(parent), std::move(name))
    {

    }

    void IContainer::AddChild(std::shared_ptr<IGuiElement> child)
    {
        m_children.push_back(std::move(child));
    }
}