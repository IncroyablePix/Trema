//
// Created by JajaFil on 2/15/2022.
//

#ifndef TREMA_CHECKBOX_H
#define TREMA_CHECKBOX_H


#include <unordered_map>
#include <functional>
#include "../GuiElement.h"

namespace Trema::View
{
    class Checkbox : public GuiElement
    {
    public:
        Checkbox(std::shared_ptr<GuiElement> parent, std::string name);
        ~Checkbox();
        void AddOnCheckListener(std::string name, std::function<void(const Checkbox& checkbox, bool checked)> listener);
        void Show() override;

        static std::shared_ptr<Checkbox> CreateCheckbox(std::shared_ptr<GuiElement> parent, std::string name);

    private:
        bool m_checked { false };
        std::unordered_map<std::string, std::function<void(const Checkbox& checkbox, bool checked)>> m_listeners;
    };
}

#endif //TREMA_CHECKBOX_H
