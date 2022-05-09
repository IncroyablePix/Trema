//
// Created by JajaFil on 3/28/2022.
//

#include "MenuOption.h"

#include <utility>
#include <future>

namespace Trema::View
{

    MenuOption::MenuOption(std::shared_ptr<GuiElement> parent, std::string name, std::string shortcut) :
            GuiElement(std::move(parent), std::move(name)),
            m_shortcut(std::move(shortcut))
    {
    }

    MenuOption::~MenuOption()
    {

    }

    void MenuOption::Show()
    {
        if (ImGui::MenuItem(NameId(), m_shortcut.c_str()))
        {
            auto future = std::async(std::launch::async, [this]()
            {
                for(const auto& [name, function] : m_listeners)
                {
                    function(*this);
                }
            });
        }
    }

    void MenuOption::AddOnClickListener(std::string name, std::function<void(const MenuOption &)> listener)
    {
        m_listeners[std::move(name)] = std::move(listener);
    }

    std::shared_ptr<MenuOption> MenuOption::CreateMenuOption(std::shared_ptr<GuiElement> parent, std::string name, std::string shortcut)
    {
        return std::make_shared<MenuOption>(std::move(parent), std::move(name), std::move(shortcut));
    }
}