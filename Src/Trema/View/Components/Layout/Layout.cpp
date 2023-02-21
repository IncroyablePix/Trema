#include "Layout.h"

namespace Trema::View
{
    Layout::Layout(std::string name) :
            GuiElement(nullptr, std::move(name))
    {
        SetIsWindow(true);
    }
}