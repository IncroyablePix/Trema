//
// Created by JajaFil on 2/14/2022.
//

#ifndef TREMA_BUTTON_H
#define TREMA_BUTTON_H

#include <unordered_map>
#include <functional>
#include "../IGuiElement.h"

namespace Trema::View
{
    class Button : public IGuiElement
    {
    public:
        Button(std::shared_ptr<IGuiElement> parent, std::string name);
        ~Button();
        void AddOnClickListener(std::string name, std::function<void(const Button& button)> listener);
        void Show() override;

        static std::shared_ptr<Button> CreateButton(std::shared_ptr<IGuiElement> parent, std::string name);
    private:
        std::unordered_map<std::string, std::function<void(const Button& button)>> m_listeners;
    };
}

#endif //TREMA_BUTTON_H