//
// Created by JajaFil on 3/28/2022.
//

#ifndef TREMA_SUBMENU_H
#define TREMA_SUBMENU_H

#include <functional>
#include "../Container/Container.h"

namespace Trema::View
{
    class SubMenu : public Container
    {
    public:
        SubMenu(std::shared_ptr<GuiElement> parent, std::string name);
        SubMenu(const SubMenu&) = delete;
        SubMenu& operator=(const SubMenu&) = delete;
        ~SubMenu() override;
        void Show() override;
        static std::shared_ptr<SubMenu> CreateSubMenu(std::shared_ptr<GuiElement> parent, std::string name);
        void AddChild(std::shared_ptr<GuiElement> child) override;
    };
}

#endif //TREMA_SUBMENU_H
