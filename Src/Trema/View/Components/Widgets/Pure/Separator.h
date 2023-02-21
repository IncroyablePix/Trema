#ifndef TREMA_SEPARATOR_H
#define TREMA_SEPARATOR_H

#include "../../GuiElement.h"

namespace Trema::View
{
    class Separator : public GuiElement
    {
    public:
        Separator(std::shared_ptr<GuiElement> parent, std::string name);
        Separator(const Separator&) = delete;
        Separator& operator=(const Separator&) = delete;
        ~Separator() override;
        void Show() override;
        static std::shared_ptr<Separator> CreateSeparator(std::shared_ptr<GuiElement> parent, std::string name);
    };
}

#endif //TREMA_SEPARATOR_H
