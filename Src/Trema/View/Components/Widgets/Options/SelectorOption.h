#ifndef TREMA_SELECTOROPTION_H
#define TREMA_SELECTOROPTION_H

#include "../../GuiElement.h"

namespace Trema::View
{
    class SelectorOption : public GuiElement
    {
    public:
        SelectorOption(std::shared_ptr<GuiElement> parent, std::string name);
        SelectorOption(const SelectorOption&) = delete;
        SelectorOption& operator=(const SelectorOption&) = delete;
        ~SelectorOption() override = default;
        void Show() override;
        static std::shared_ptr<SelectorOption> CreateSelectorOption(std::shared_ptr<GuiElement> parent, std::string name);
    };
}

#endif //TREMA_SELECTOROPTION_H
