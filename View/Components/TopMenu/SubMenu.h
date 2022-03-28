//
// Created by JajaFil on 3/28/2022.
//

#ifndef TREMA_SUBMENU_H
#define TREMA_SUBMENU_H

#include <functional>
#include "../Container/IContainer.h"

namespace Trema::View
{
    class SubMenu : public IContainer
    {
    public:
        SubMenu(std::shared_ptr<IGuiElement> parent, std::string name);
        ~SubMenu();
        void Show() override;
        static std::shared_ptr<SubMenu> CreateSubMenu(std::shared_ptr<IGuiElement> parent, std::string name);
        void AddChild(std::shared_ptr<IGuiElement> child) override;

    private:
    };
}

#endif //TREMA_SUBMENU_H
