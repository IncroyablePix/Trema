//
// Created by JajaFil on 2/13/2022.
//

#include "Container.h"

#include <utility>

namespace Trema::View
{
    bool Container::SubContainer = false;

    Container::Container(std::shared_ptr<GuiElement> parent, std::string name) :
            GuiElement(std::move(parent), std::move(name))
    {

    }

    void Container::AddChild(std::shared_ptr<GuiElement> child)
    {
        m_children.push_back(std::move(child));
    }
}