//
// Created by JajaFil on 2/14/2022.
//

#ifndef TREMA_RADIO_H
#define TREMA_RADIO_H


#include <functional>
#include "../../GuiElement.h"
#include "../../Container/Container.h"

namespace Trema::View
{
    class Radio : public Container
    {
    public:
        Radio(std::shared_ptr<GuiElement> parent, std::string name);
        Radio(const Radio&) = delete;
        Radio& operator=(const Radio&) = delete;
        ~Radio() override;
        void AddOption(std::string name);
        void AddChild(std::shared_ptr<GuiElement> child) override;

        void Show() override;

        inline void SetOption(int option) { m_option = option; }
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
