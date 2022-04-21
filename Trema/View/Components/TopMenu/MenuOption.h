//
// Created by JajaFil on 3/28/2022.
//

#ifndef TREMA_MENUOPTION_H
#define TREMA_MENUOPTION_H


#include <functional>
#include "../IGuiElement.h"

namespace Trema::View
{
    class MenuOption : public IGuiElement
    {
    public:
        MenuOption(std::shared_ptr<IGuiElement> parent, std::string name, std::string shortcut);
        ~MenuOption();
        void Show() override;
        void AddOnClickListener(std::string name, std::function<void(const MenuOption& button)> listener);
        static std::shared_ptr<MenuOption> CreateMenuOption(std::shared_ptr<IGuiElement> parent, std::string name, std::string shortcut);

    private:
        std::unordered_map<std::string, std::function<void(const MenuOption& button)>> m_listeners;
        std::string m_shortcut;
    };
}

#endif //TREMA_MENUOPTION_H
