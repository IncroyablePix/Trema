#include "SelectorOption.h"
#include "../DisplayException.h"

#include <utility>

namespace Trema::View
{

    SelectorOption::SelectorOption(std::shared_ptr<GuiElement> parent, std::string name) :
            GuiElement(std::move(parent), std::move(name))
    {

    }

    void SelectorOption::Show()
    {
        throw DisplayException("Cannot display element SelectorOption");
    }

    std::shared_ptr<SelectorOption>
    SelectorOption::CreateSelectorOption(std::shared_ptr<GuiElement> parent, std::string name)
    {
        return std::make_shared<SelectorOption>(std::move(parent), std::move(name));
    }
}