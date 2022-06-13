//
// Created by JajaFil on 2/13/2022.
//

#ifndef TREMA_TOPMENU_H
#define TREMA_TOPMENU_H


#include "../GuiElement.h"
#include "../Container/Container.h"

namespace Trema::View
{
    class TopMenu : public Container
    {
    public:
        explicit TopMenu(std::string name);
        TopMenu(const TopMenu&) = delete;
        TopMenu& operator=(const TopMenu&) = delete;
        ~TopMenu() override;
        void Show() override;
        void AddChild(std::shared_ptr<GuiElement> child) override;
        static std::shared_ptr<TopMenu> CreateTopMenu(std::string name);
    };
}

#endif //TREMA_TOPMENU_H
