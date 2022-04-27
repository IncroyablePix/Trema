//
// Created by JajaFil on 3/28/2022.
//

#ifndef TREMA_SEPARATOR_H
#define TREMA_SEPARATOR_H

#include "../IGuiElement.h"

namespace Trema::View
{
    class Separator : public IGuiElement
    {
    public:
        Separator(std::shared_ptr<IGuiElement> parent, std::string name);
        ~Separator();
        void Show() override;
        static std::shared_ptr<Separator> CreateSeparator(std::shared_ptr<IGuiElement> parent, std::string name);
    };
}

#endif //TREMA_SEPARATOR_H
