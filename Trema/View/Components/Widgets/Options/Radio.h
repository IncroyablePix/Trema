//
// Created by JajaFil on 2/14/2022.
//

#ifndef TREMA_RADIO_H
#define TREMA_RADIO_H


#include <functional>
#include "../../GuiElement.h"
#include "../../Container/IContainer.h"

namespace Trema::View
{
    class Radio : public IContainer
    {
    public:
        Radio(std::shared_ptr<GuiElement> parent, std::string name);
        ~Radio();
        void AddOption(std::string name);
        void AddChild(std::shared_ptr<GuiElement> child) override;

        void Show() override;

        inline int GetOptionIndex() const { return m_option; }
        inline std::string GetOption() const { return m_options[m_option]; }

        void AddOnClickListener(std::string name, std::function<void(const std::string&)> listener);
        static std::shared_ptr<Radio> CreateRadio(std::shared_ptr<GuiElement> parent, std::string name);

    private:
        int m_option { 0 };
        std::vector<std::string> m_options;
        std::unordered_map<std::string, std::function<void(const std::string& option)>> m_listeners;
    };
}

#endif //TREMA_RADIO_H
