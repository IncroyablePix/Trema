#include "Container.h"

#include <utility>

namespace Trema::View
{
    bool Container::SubContainer = false;

    Container::Container(std::shared_ptr<GuiElement> parent, std::string name) :
            GuiElement(std::move(parent), std::move(name))
    {
        SetIsWindow(true);
    }

    void Container::AddChild(std::shared_ptr<GuiElement> child)
    {
        m_children.push_back(std::move(child));
    }
}