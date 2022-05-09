//
// Created by JajaFil on 2/13/2022.
//

#include "IContainer.h"

#include <utility>

namespace Trema::View
{
    bool IContainer::SubContainer = false;

    IContainer::IContainer(std::shared_ptr<GuiElement> parent, std::string name) :
            GuiElement(std::move(parent), std::move(name))
    {

    }

    void IContainer::AddChild(std::shared_ptr<GuiElement> child)
    {
        m_children.push_back(std::move(child));
    }
}