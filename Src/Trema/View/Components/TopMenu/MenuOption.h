#ifndef TREMA_MENUOPTION_H
#define TREMA_MENUOPTION_H


#include <functional>
#include "../GuiElement.h"

namespace Trema::View
{
    class MenuOption : public GuiElement
    {
    public:
        MenuOption(std::shared_ptr<GuiElement> parent, std::string name, std::string shortcut);
        MenuOption(const MenuOption&) = delete;
        MenuOption& operator=(const MenuOption&) = delete;
        ~MenuOption() override;
        void Show() override;
        void AddOnClickListener(std::string name, std::function<void(const MenuOption& button)> listener);
        static std::shared_ptr<MenuOption> CreateMenuOption(std::shared_ptr<GuiElement> parent, std::string name, std::string shortcut);

    private:
        std::unordered_map<std::string, std::function<void(const MenuOption& button)>> m_listeners;
        std::string m_shortcut;
    };
}

#endif //TREMA_MENUOPTION_H
